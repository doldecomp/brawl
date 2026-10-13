#pragma once

#include <StaticAssert.h>
#include <so/so_connectable.h>
#include <so/so_general_flag.h>
#include <so/so_null.h>
#include <types.h>
#include <so/so_array_vector_calculator.h>
#include <bitset>

template <class T>
class soSet {
    T* m_elements;
    size_t m_size;

public:
    T* elements() {
        return m_elements;
    }

    u32 size() {
        return m_size;
    }
};

template <class T>
class soArrayFixed : public soNullableInterface {
public:

    virtual bool isNull() const { return false; }
    virtual T& at(s32 index) = 0;
    virtual const T& at(s32 index) const = 0;
    virtual s32 size() const = 0;
    virtual bool isEmpty() const { return this->size() == 0; }
    virtual ~soArrayFixed() { };
};

template<typename T>
class soArrayFixedNull : soArrayFixed<T> {
public:
    virtual bool isNull() const { return true; }
    virtual T& at(s32 index) {
        static T m_nullElement;
        return m_nullElement;
    };
    virtual const T& at(s32 index) const {
        static T m_nullElement;
        return m_nullElement;
    };
    virtual s32 size() const { return 0; }
    virtual ~soArrayFixedNull() { }
};

template <class T>
class soArrayContractible : public soArrayFixed<T> {
public:
    virtual ~soArrayContractible() { }
    virtual void shift() = 0;
    virtual void pop() = 0;
    virtual void clear() = 0;
};

template<typename T>
class soArrayContractibleTable : public soArrayContractible<T>,
                                 public soConnectable<soArrayContractibleTable<T> > {
    T* m_elements;
    s32 m_size;
public:
    soArrayContractibleTable() : m_elements(nullptr), m_size(0) { }
    soArrayContractibleTable(T* elmnts, s32 size) : m_elements(elmnts), m_size(size) {
        if (!elmnts) {
            this->m_size = 0;
        }
    }

    virtual ~soArrayContractibleTable() { }

    soArrayContractibleTable& operator=(const soArrayContractibleTable& other) {
        if (this == &other)
            return *this;
        soConnectable<soArrayContractibleTable<T> >::operator=(other);
        const bool noElements = (other.m_elements == nullptr);
        m_elements = other.m_elements;
        m_size = other.m_size;
        if (noElements)
            m_size = 0;
        return *this;
    }

    virtual T& at(s32 index) { return atSub(index); }
    virtual const T& at(s32 index) const { return atSub(index); }

    virtual void shift() {
        if (!this->isEmpty()) {
            if (m_size > 0) {
                if (--m_size <= 0) {
                    m_elements = nullptr;
                } else {
                    m_elements++;
                }
            } else if (this->m_link) {
                this->m_link->shift();
            }
        }
    }

    virtual void pop() {
        if (this->m_link && !this->m_link->isEmpty()) {
            this->m_link->pop();
        } else if (m_size > 0) {
            m_size--;
        }
    }

    virtual void clear() {
        if (this->m_link) {
            this->m_link->clear();
        }
        m_elements = nullptr;
        m_size = 0;
    }

    virtual s32 size() const {
        s32 res = m_size;
        if (!m_elements) {
            res = 0;
        }
        if (this->m_link) {
            return res + this->m_link->size();
        }
        return res;
    }

    bool isNull() const { return false; }

    virtual T& atSub(s32 index) const {
        if (index >= m_size && this->m_link) {
            return this->m_link->at(index - m_size);
        }
        return m_elements[index];
    }
};

template<typename T>
class soArrayContractibleNull : public soArrayContractible<T> {

public:
    bool isNull() const { return true; }
    virtual T& at(s32 index) {
        static T nullObject;
        return nullObject;
    }
    virtual const T& at(s32 index) const {
        static T nullObject;
        return nullObject;
    }
    virtual s32 size() const {
        return 0;
    }
    virtual ~soArrayContractibleNull() { }
    virtual void shift() { }
    virtual void pop() { }
    virtual void clear() { }
};

template <class T>
class soArray : public soArrayContractible<T> {
public:
    virtual ~soArray() {};

    virtual void unshift(const T&) = 0;
    virtual void push(const T&) = 0;
    virtual void insert(s32, const T&) = 0;
    virtual void erase(s32) = 0;
    virtual s32 capacity() const = 0;
    virtual bool isFull() const = 0;
    virtual void set(s32 startingIndex, const T& element, s32 numIndicesToSet) = 0;
};

template <class T>
class soArrayNull : public soArray<T> {

public:
    virtual bool isNull() const { return true; }
    virtual T& at(s32 index) {
        static T m_nullElement;
        return m_nullElement;
    };
    virtual const T& at(s32 index) const {
        static T m_nullElement;
        return m_nullElement;
    };
    virtual s32 size() const { return 0; }
    virtual ~soArrayNull() { }
    virtual void shift() { return; }
    virtual void pop() { return; }
    virtual void clear() { return; }
    virtual void unshift(const T&) { return; }
    virtual void push(const T&) { return; }
    virtual void insert(s32, const T&) { return; }
    virtual void erase(s32) { return; }
    virtual s32 capacity() const { return 0; }
    virtual bool isFull() const { return true; }
    virtual void set(s32 startingIndex, const T& element, s32 numIndicesToSet) { }

    soArrayNull() { }
    soArrayNull(s32 size, s32 = 0) { }
    soArrayNull(s32 size, const T& element, s32) { }
};

template <typename ElementTy, typename IndexTy>
struct soArrayListUnit {
    u8 m_inUse : 1;
    ElementTy m_element;
    IndexTy m_prev;
    IndexTy m_next;

    static const s32 End = -1;

    soArrayListUnit() : m_inUse(false), m_prev(End), m_next(End) { }
    ~soArrayListUnit() { }

    void setNext(IndexTy n) { m_next = n; }
};

template <typename T>
class soEnumerator : public soNullable {
public:
    virtual bool next() = 0;
    virtual bool hasNext() const = 0;
    virtual bool isEnd() const = 0;
    virtual T& getCurrent() const = 0;
    virtual ~soEnumerator() = 0;
};

template <typename ElementTy, typename IndexTy>
struct soArrayListEnumerator : public soEnumerator<ElementTy> {
    soArrayListUnit<ElementTy, IndexTy>* m_units;
    s32 m_next;

    static const s32 End = -1;
public:
    soArrayListEnumerator() : m_units(nullptr), m_next(End) { }
    soArrayListEnumerator(soArrayListUnit<ElementTy, IndexTy>* units, s32 next) :
        m_units(units), m_next(next) { }
    s32 getNext() const { return m_next; }

    // TODO: verify whether ft_pikmin code triggers the generation
    // of an implicitly-defined copy-assign and copy-ctor

    virtual bool next() {
        if (!hasNext()) {
            m_next = End;
            return false;
        }
        m_next = m_units[m_next].m_next;
        return true;
    }

    virtual bool hasNext() const {
        return m_units[m_next].m_next >= 0;
    }

    virtual bool isEnd() const {
        return m_next < 0;
    }

    virtual ElementTy& getCurrent() const {
        return m_units[m_next].m_element;
    }

    virtual ~soArrayListEnumerator() { }
};

// A dynamic array of soArrayListUnits, but with a fixed maximum capacity.
// Each unit has a logical "position" corresponding to an actual "index"
// in the internal array. This distinction is implemented via an intrusive
// doubly-linked list connecting the units; see getArrayIndex for details.
template <typename T, s32 C>
class soArrayList : public soArray<T> {
    // The index of the next available free unit in the list
    s32 m_freeIndex : sizeof(bit_width<C>) + 1;
    // The index of logical position 0
    s32 m_topIndex : sizeof(bit_width<C>) + 1;
    // The index of logical position size() - 1
    s32 m_lastIndex : sizeof(bit_width<C>) + 1;
    // The current number of allocated units
    s32 m_size : sizeof(bit_width<C>) + 1;

    soArrayListUnit<T, s8> m_units[C];

    // Allocate an soArrayListUnit from the internal list,
    // incrementing the size and returning the index of the
    // allocated unit. If idx is negative, get the next available
    // free unit. In practice, idx is always negative
    s32 shiftFreeArrayIndex(s32 idx);
    // Get the index of the element at position pos
    s32 getArrayIndex(s32 pos) const;
    // Make space in the list such that a new element may be assigned
    // to the returned index, if space is available. The index returned
    // corresponds to the logical position prevPos+1
    s32 insertSub(s32 prevPos, s32 where = End);
    // Make all necessary updates to the internal linked list of units
    // to erase the element at idx
    void eraseSub(s32 idx);

    s32 getFreeIndex() const { return m_freeIndex; }

    // Mark the element at idx as deleted, and set idx to m_freeIndex
    void clearElement(s32 idx) {
        if (idx >= 0) {
            m_units[idx].m_next = m_freeIndex;
            m_units[idx].m_prev = End;
            m_units[idx].m_inUse = false;
            if (m_freeIndex > 0)
                m_units[idx].m_prev = idx;
            m_freeIndex = idx;
            m_size--;
        }
    }

    static const s32 End = -1;
public:
    // Note that the call to clear() immediately overwrites a 0 to m_freeIndex, so
    // allocations begin at the start of the fixed internal array.
    soArrayList() : m_freeIndex(End), m_topIndex(End), m_lastIndex(End) {
        clear();
    }

    virtual bool isNull() const {
        return false;
    }

    virtual T& at(s32 i) {
        s32 idx = getArrayIndex(i);
        if (this->isEmpty() != true && idx >= 0)
            static_cast<void>(capacity());
        return m_units[idx].m_element;
    }

    virtual const T& at(s32 i) const {
        s32 idx = getArrayIndex(i);
        if (this->isEmpty() != true && idx >= 0)
            static_cast<void>(capacity());
        return m_units[idx].m_element;
    }

    virtual s32 size() const {
        return m_size;
    }

    virtual ~soArrayList() { }

    // Erase the element in the first position
    virtual void shift() {
        eraseSub(getArrayIndex(0));
    }

    // Erase the element in the last position
    virtual void pop() {
        eraseSub(getArrayIndex(size() - 1));
    }

    // Erase all elements of the list, resetting the bitfields and linked list
    virtual void clear() {
        m_freeIndex = 0;
        m_topIndex = End;
        m_lastIndex = End;
        m_size = 0;

        if (capacity() == 1) {
            m_units[0].m_prev = End;
            m_units[0].m_next = End;
            m_units[0].m_inUse = false;
        } else {
            for (s32 i = 0; i < capacity(); i++) {
                m_units[i].m_prev = i - 1;
                m_units[i].m_next = i + 1;
                m_units[i].m_inUse = false;
            }
            m_units[capacity() - 1].setNext(End);
        }
    }

    // Prepend elm to the list, if space is available
    virtual void unshift(const T& elm) {
        s32 idx = insertSub(-1);
        if (idx >= 0)
            m_units[idx].m_element = elm;
    }

    // Append elm to the list, if space is available
    virtual void push(const T& elm) {
        s32 idx = insertSub(size() - 1);
        if (idx >= 0)
            m_units[idx].m_element = elm;
    }

    // Insert elm at position i of the list, if i is in range and space is
    // available
    virtual void insert(s32 pos, const T& elm) {
        s32 idx = insertSub(pos - 1);
        if (idx >= 0)
            m_units[idx].m_element = elm;
    }

    // Erase the element at position pos
    virtual void erase(s32 pos) {
        eraseSub(getArrayIndex(pos));
    }

    virtual s32 capacity() const {
        return C;
    }

    virtual bool isFull() const {
        return m_freeIndex < 0;
    }

    // Starting at position pos, assign elm to consecutive elements, stopping
    // when either count or the end of the list has been reached
    virtual void set(s32 pos, const T& elm, s32 count) {
        if (count) {
            if (count + pos >= size())
                count = size() - pos;
            s32 curr = m_topIndex;
            while (count > 0) {
                if (pos > 0)
                    pos--;
                else {
                    m_units[curr].m_element = elm;
                    count--;
                }
                if ((curr = m_units[curr].m_next) < 0)
                    break;
            }
        }
    }

    // TODO: check implicit generation by <wnPikminPikmin*, 10> for these two
    soArrayListEnumerator<T, s8> getEnumerator() {
        return soArrayListEnumerator<T, s8>(m_units, m_topIndex);
    }

    // Erase the element at position enm.getNext()
    void erase(const soArrayListEnumerator<T, s8>& enm) {
        eraseSub(enm.getNext());
    }

    soArrayListUnit<T, s8>* getUnits() { return m_units; }
};

template <typename T, s32 C>
s32 soArrayList<T, C>::shiftFreeArrayIndex(s32 idx) {
    if (isFull() == true)
        return End;
    if (idx < 0) {
        s32 freeIndex = getFreeIndex();
        m_freeIndex = m_units[m_freeIndex].m_next;
        if (m_freeIndex > 0)
            m_units[m_freeIndex].m_prev = End;
        m_size++;
        return freeIndex;
    }

    // Note: the remainder of this function is unused, since
    // all callers pass -1 for idx. It apparently removes the
    // soArrayListUnit at position idx from the doubly-linked list.
    if (idx >= capacity())
        return End;
    const soArrayListUnit<T, s8>& curr = m_units[idx];
    if (static_cast<bool>(curr.m_inUse) == true)
        return End;
    s32 next = curr.m_next;
    s32 prev = curr.m_prev;
    if (prev < 0 && next < 0)
        m_freeIndex = End;
    else if (prev < 0) {
        m_units[next].m_prev = End;
        m_freeIndex = curr.m_next;
    } else if (next < 0)
        m_units[prev].m_next = End;
    else {
        m_units[prev].m_next = next;
        m_units[next].m_prev = prev;
    }
    m_size++;
    return idx;
}

template <typename T, s32 C>
s32 soArrayList<T, C>::getArrayIndex(s32 pos) const {
    if (pos < 0 || pos >= size())
        return End;
    if (pos == 0)
        return m_topIndex;
    if (pos == size() - 1)
        return m_lastIndex;
    s32 count = pos;
    s32 curr = m_topIndex;
    if (pos > size() / 2) {
        // Step from the back of the list instead
        count = size() - pos - 1;
        curr = m_lastIndex;
    }
    for (s32 i = 0; i < size(); i++) {
        if (i == count)
            return curr;
        if (pos > size() / 2)
            curr = m_units[curr].m_prev;
        else
            curr = m_units[curr].m_next;
        if (curr < 0)
            break;
    }
    return End;
}

template <typename T, s32 C>
s32 soArrayList<T, C>::insertSub(s32 prevPos, s32 where) {
    s32 prevIdx = End;
    if (prevPos >= 0) {
        prevIdx = getArrayIndex(prevPos);
        if (prevIdx < 0)
            return End;
    }
    s32 freeIdx = shiftFreeArrayIndex(where);
    if (freeIdx < 0)
        return End;

    s32 newNext = End;
    if (prevIdx < 0)
        newNext = m_topIndex;
    else if (m_units[prevIdx].m_next >= 0)
        newNext = m_units[prevIdx].m_next;

    if (prevIdx >= 0)
        m_units[prevIdx].m_next = freeIdx;
    else
        m_topIndex = freeIdx;

    m_units[freeIdx].m_prev = prevIdx;
    if (newNext >= 0)
        m_units[newNext].m_prev = freeIdx;
    else
        m_lastIndex = freeIdx;
    m_units[freeIdx].m_next = newNext;
    m_units[freeIdx].m_inUse = true;
    return freeIdx;
}

template <typename T, s32 C>
void soArrayList<T, C>::eraseSub(s32 idx) {
    if (idx < 0 || idx >= capacity())
        return;
    if (size() == 1) {
        m_topIndex = End;
        m_lastIndex = End;
        clearElement(idx);
    } else {
        s32 next = getUnits()[idx].m_next;
        s32 prev = getUnits()[idx].m_prev;

        // Remove from list
        if (prev < 0) {
            m_units[next].m_prev = End;
            m_topIndex = next;
        } else if (next < 0) {
            m_units[prev].m_next = End;
            m_lastIndex = prev;
        } else {
            m_units[prev].m_next = next;
            m_units[next].m_prev = prev;
        }
        clearElement(idx);
    }
}

class soArrayVectorCalcInterface {
public:
    virtual void substitution(s32, s32) = 0;
    virtual void onFull() = 0;
    virtual void offFull() = 0;
    virtual void setTopIndex(s32) = 0;
    virtual void setLastIndex(s32) = 0;
    virtual ~soArrayVectorCalcInterface() { }
};

template <class T>
class soArrayVectorAbstract : public soArray<T>, public soArrayVectorCalcInterface {
public:
    virtual bool isNull() const {
        return false;
    }
    virtual T& at(s32 index) {
        return this->atFastAbstractSub(index);
    }
    virtual const T& at(s32 index) const {
        return this->atFastAbstractSub(index);
    }
    virtual ~soArrayVectorAbstract() { }
    virtual void shift() {
        soArrayVectorCalculator::shift(*this, this->isEmpty(), this->capacity(), this->getTopIndex());
        this->setSize(this->size() - 1);
    }
    virtual void pop() {
        soArrayVectorCalculator::pop(*this, this->isEmpty(), this->capacity(), this->getLastIndex());
        this->setSize(this->size() - 1);
    }
    virtual void clear() {
        soArrayVectorCalculator::clear(*this);
        this->setSize(0);
    }
    virtual void unshift(const T& newElement) {
        s32 topIndex = soArrayVectorCalculator::unshift(*this, this->isFull(), this->capacity(), this->getTopIndex(), this->getLastIndex());
        T& element = this->getArrayValueConst(topIndex);
        element = newElement;
        this->setSize(this->size() + 1);
    }
    virtual void push(const T& newElement) {
        s32 lastIndex = soArrayVectorCalculator::push(*this, this->isFull(), this->capacity(), this->getTopIndex(), this->getLastIndex());
        T& element = this->getArrayValueConst(lastIndex);
        element = newElement;
        this->setSize(this->size() + 1);
    }
    virtual void insert(s32 index, const T& newElement) {
        s32 lastIndex = soArrayVectorCalculator::insert(*this, index, this->isFull(), this->size(), this->capacity(), this->getTopIndex(), this->getLastIndex());
        T& element = this->getArrayValueConst(lastIndex);
        element = newElement;
        this->setSize(this->size() + 1);
    }
    virtual void erase(s32 index) {
        soArrayVectorCalculator::erase(*this, index, this->size(), this->capacity(), this->getTopIndex(), this->getLastIndex());
        this->setSize(this->size() - 1);
    }
    virtual s32 capacity() const = 0;

    virtual void set(s32 start, const T& elm, s32 count) {
        int c = count;
        if (c + start >= this->size())
            c = this->size() - start;
        for (s32 i = 0; i < c; i++)
            this->at(start+i) = elm;
    }

    virtual T& atFastAbstractSub(s32 index) const = 0;
    virtual void substitution(s32 subIndex, s32 targetIndex) {
        T& subElement = this->getArrayValueConst(subIndex);
        T& targetElement = this->getArrayValueConst(targetIndex);
        targetElement = subElement;
    }
    virtual T& getArrayValueConst(s32) = 0;
    virtual s32 getTopIndex() const = 0;
    virtual s32 getLastIndex() const = 0;
    virtual void setSize(s32) = 0;
};

template <class T, s32 C>
class soArrayVector : public soArrayVectorAbstract<T> {
    s32 m_topIndex : sizeof(bit_width<C>) + 1;
    s32 m_lastIndex : sizeof(bit_width<C>) + 1;
    s32 m_size : sizeof(bit_width<C>) + 1;
    u32 m_isFull : 1;

    T m_elements[C];

public:
    virtual s32 size() const { return m_size; }
    virtual ~soArrayVector() { }
    virtual s32 capacity() const { return C; }
    virtual bool isFull() const { return m_isFull; }

    virtual T& atFastAbstractSub(s32 index) const {
        return atFast(index);
    }
    virtual T& getArrayValueConst(s32 index) {
        return this->m_elements[index];
    }
    virtual s32 getTopIndex() const { return m_topIndex; }
    virtual s32 getLastIndex() const { return m_lastIndex; }
    virtual void setSize(s32 size) { m_size = size; }
    virtual void setTopIndex(s32 topIndex) { m_topIndex = topIndex; }
    virtual void setLastIndex(s32 lastIndex) { m_lastIndex = lastIndex; }
    virtual void onFull() { m_isFull = true; }
    virtual void offFull() { m_isFull = false; }

    soArrayVector() : m_topIndex(0), m_lastIndex(0), m_size(0), m_isFull(false) { }

    soArrayVector(s32 size, s32 = 0) {
        m_topIndex = 0;
        m_lastIndex = 0;
        m_isFull = false;
        m_size = size;
        soArrayVectorCalculator::postInitialize(*this, size, C);
    }
    soArrayVector(s32 size, const T& element, s32) {
        m_topIndex = 0;
        m_lastIndex = 0;
        m_size = 0;
        m_isFull = false;
        size = soArrayVectorCalculator::resize(*this, size, this->isEmpty(), this->isFull(), this->capacity(), this->getTopIndex(), this->getLastIndex());
        for (u32 i = 0; i < size; i++) {
            this->push(element);
        }
    }
    T& atFast(s32 idx) const {
        s32 i = m_topIndex + idx;
        if (i >= C)
            i -= C;
        return const_cast<T&>(m_elements[i]);
    }
};

template <class T>
class soArrayVector<T, 0> : public soArrayNull<T> {
public:
    inline soArrayVector() : soArrayNull<T>() { }
    inline soArrayVector(s32 size, s32 unk) : soArrayNull<T>(size, unk) { }
    inline soArrayVector(s32 size, const T& element, s32 unk) : soArrayNull<T>(size, element, unk) { }
};

template<typename T>
soArray<T>& getNullArray() {
    static soArrayNull<T> NullObj;
    return NullObj;
}

extern soArrayNull<s32> g_s32ArrayNull;
extern soArrayNull<float> g_floatArrayNull;
extern soArrayNull<soGeneralFlag<s32> > g_s32GeneralFlagArrayNull;
