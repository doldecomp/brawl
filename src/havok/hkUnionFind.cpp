#include <havok/hkUnionFind.h>

static inline int* parentData(hkArrayBase* a) {
    return (int*)a->m_data;
}

hkUnionFind::hkUnionFind(hkArrayBase& parents, int numElements) {
    m_parents = &parents;
    if ((parents.m_capacityAndFlags & hkArrayBase::CAPACITY_MASK) < numElements) {
        int newCapacity = (parents.m_capacityAndFlags & hkArrayBase::CAPACITY_MASK) * 2;
        if (numElements >= newCapacity) {
            newCapacity = numElements;
        }
        hkArrayUtil::_reserve(&parents, newCapacity, 4);
    }
    parents.m_size = numElements;
    for (int i = 0; i < numElements; i++) {
        parentData(m_parents)[i] = -1;
    }
}

void hkUnionFind::addEdge(int a, int b) {
    if (a > b) {
        int t = a;
        a = b;
        b = t;
    }
    int ra = a;
    while (parentData(m_parents)[ra] >= 0) {
        ra = parentData(m_parents)[ra];
    }
    int i = a;
    while (parentData(m_parents)[i] >= 0) {
        int next = parentData(m_parents)[i];
        parentData(m_parents)[i] = ra;
        i = next;
    }
    int rb = b;
    while (parentData(m_parents)[rb] >= 0) {
        rb = parentData(m_parents)[rb];
    }
    i = b;
    while (parentData(m_parents)[i] >= 0) {
        int next = parentData(m_parents)[i];
        parentData(m_parents)[i] = rb;
        i = next;
    }
    if (ra == rb) {
        return;
    }
    int* data = parentData(m_parents);
    if (ra < rb) {
        data[ra] = data[ra] + data[rb];
        parentData(m_parents)[rb] = ra;
    } else {
        data[rb] = data[rb] + data[ra];
        parentData(m_parents)[ra] = rb;
    }
}

void hkUnionFind::collapseTree() {
    int* p = parentData(m_parents);
    int* end = p + m_parents->m_size;
    for (; p != end; p++) {
        if (*p >= 0) {
            while (parentData(m_parents)[*p] >= 0) {
                *p = parentData(m_parents)[*p];
            }
        }
    }
}

void hkUnionFind::assignGroups(hkArrayBase& groupSizes) {
    collapseTree();
    int numGroups = 0;
    for (int i = 0; i < m_parents->m_size; i++) {
        int p = parentData(m_parents)[i];
        if (p < 0) {
            int size = -p;
            if (groupSizes.m_size == (groupSizes.m_capacityAndFlags & hkArrayBase::CAPACITY_MASK)) {
                hkArrayUtil::_reserveMore(&groupSizes, 4);
            }
            ((int*)groupSizes.m_data)[groupSizes.m_size++] = size;
            parentData(m_parents)[i] = numGroups;
            numGroups++;
        } else {
            int* data = parentData(m_parents);
            data[i] = data[p];
        }
    }
    int n = groupSizes.m_size;
    int largest = 0;
    int largestSize = ((int*)groupSizes.m_data)[0];
    for (int k = 1; k < n; k++) {
        if (((int*)groupSizes.m_data)[k] > largestSize) {
            largestSize = ((int*)groupSizes.m_data)[k];
            largest = k;
        }
    }
    if (largest != 0) {
        hkLocalBuffer<int> perm(n);
        for (int k = 0; k < n; k++) {
            perm[k] = k;
        }
        perm[0] = largest;
        perm[largest] = 0;
        ((int*)groupSizes.m_data)[largest] = ((int*)groupSizes.m_data)[0];
        ((int*)groupSizes.m_data)[0] = largestSize;
        for (int i = 0; i < m_parents->m_size; i++) {
            int* data = parentData(m_parents);
            data[i] = perm[data[i]];
        }
    }
}
