#include <havok/hkStructureLayout.h>
#include <havok/hkIostream.h>
#include <havok/hkError.h>

hkStructureLayout::LayoutRules hkStructureLayout::HostLayoutRules = {4, hkBool(false), 1, 1};

hkStructureLayout::hkStructureLayout() {
    m_rules.m_bytesInPointer = HostLayoutRules.m_bytesInPointer;
    m_rules.m_littleEndian = HostLayoutRules.m_littleEndian;
    m_rules.m_reusePaddingOptimization = HostLayoutRules.m_reusePaddingOptimization;
    m_rules.m_emptyBaseClassOptimization = HostLayoutRules.m_emptyBaseClassOptimization;
}

static int computeMemberSize(const hkClassMember& m, const hkStructureLayout::LayoutRules& rules, int type) {
    int size = 0;
    switch (type) {
    case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9: case 10:
    case 11: case 12: case 13: case 14: case 15: case 16: case 17: case 18: case 24:
        size = m.getSizeInBytes();
        break;
    case hkClassMember::TYPE_POINTER:
    case hkClassMember::TYPE_FUNCTIONPOINTER:
    case hkClassMember::TYPE_CSTRING: {
        int p = rules.m_bytesInPointer;
        size = p * (m.getCstyleArraySize() ? m.getCstyleArraySize() : 1);
        break;
    }
    case hkClassMember::TYPE_VARIANT:
        size = rules.m_bytesInPointer * 2;
        break;
    case hkClassMember::TYPE_ARRAY:
        size = 4;
    case hkClassMember::TYPE_SIMPLEARRAY:
        size = size + rules.m_bytesInPointer + 4;
        break;
    case hkClassMember::TYPE_STRUCT: {
        int objSize = m.getStructClass()->getObjectSize();
        size = objSize * (m.getCstyleArraySize() ? m.getCstyleArraySize() : 1);
        break;
    }
    case hkClassMember::TYPE_ZERO:
        size = computeMemberSize(m, rules, m.m_subtype);
        break;
    case hkClassMember::TYPE_HOMOGENEOUSARRAY:
        size = rules.m_bytesInPointer * 2 + 4;
        break;
    case hkClassMember::TYPE_INPLACEARRAY:
        break;
    default: {
        char buf[0x200];
        hkOstream os(buf, sizeof(buf), hkBool(true));
        os << "Unknown class member type in structureLayout::getMemberSize().";
        hkError::s_instance->message(3, 0x50A18B58, buf, "hkStructureLayout.cpp", 0xBB);
        break;
    }
    }
    return size;
}

static int isBasicPointerType(int type) {
    int r = 0;
    // MATCH-ONLY: the reference keeps the two uses of (type - 0x14) from sharing a register
    int& tmp0 = type;
    if ((unsigned)(type - 0x14) <= 9 && ((1 << (tmp0 - 0x14)) & 0x3C5) != 0) {
        r = 1;
    }
    return (u32)r;
}

static int isPointerType(const hkClassMember& m) {
    int r = 0;
    if (isBasicPointerType(m.m_type) || (m.m_type == 0x13 && isBasicPointerType(m.m_subtype))) {
        r = 1;
    }
    return r;
}

static int getLayoutAlignment(const hkClassMember& m, int type, int ptrAlign) {
    int align = -1;
    if (type == 0x17) {
        return -1;
    }
    if (type < 0x17) {
        if (type == 0x13) {
            return getLayoutAlignment(m, m.m_subtype, ptrAlign);
        }
        if (type > 0x12) {
            return ptrAlign;
        }
        if (type < 0) {
            return -1;
        }
    } else {
        if (type == 0x19) {
            align = 1;
            const hkClass* k = m.getStructClass();
            for (int i = 0; i < k->getNumMembers(); i++) {
                const hkClassMember& sub = k->getMember(i);
                int a = getLayoutAlignment(sub, sub.m_type, ptrAlign);
                if (a > align) {
                    align = a;
                }
            }
            return align;
        }
        if (type > 0x18) {
            if (type < 0x1E) {
                return ptrAlign;
            }
            return -1;
        }
    }
    return m.getAlignment();
}

static void retargetClassInplace(hkClass* klass, const hkStructureLayout::LayoutRules& rules,
                                 hkPointerMapBase<hkUlong>& done) {
    done.insert((hkUlong)klass, 0);
    int numMembers = klass->getNumMembers();
    for (int i = 0; i < numMembers; i++) {
        hkClassMember& m = (hkClassMember&)klass->getMember(i);
        bool recurse = false;
        if (m.m_class != 0) {
            if (!hkPointerMapHasKey(done, (hkUlong)m.getStructClass())) {
                recurse = true;
            }
        }
        if (recurse) {
            retargetClassInplace((hkClass*)m.getStructClass(), rules, done);
        }
    }

    hkArray<hkClass*> chain;
    hkClass* cur = klass;
    while (cur != 0) {
        chain.insertAt(0, cur);
        cur = (hkClass*)cur->getParent();
    }

    int ptrSize = rules.m_bytesInPointer;
    int offset = 0;
    int maxAlign = 1;
    int idx = 0;
    int byteIdx = 0;
    cur = 0;
    while (idx < chain.getSize()) {
        hkClass* c = chain[idx];
        for (int j = 0; j < c->getNumDeclaredInterfaces(); j++) {
            int rem = offset - (offset / ptrSize) * ptrSize;
            if (rem != 0) {
                offset = offset - rem + ptrSize;
            }
            offset += ptrSize;
            if (maxAlign < ptrSize) {
                maxAlign = ptrSize;
            }
        }
        for (int j = 0; j < c->getNumDeclaredMembers(); j++) {
            hkClassMember& m = (hkClassMember&)c->getDeclaredMember(j);
            if (offset == 0 && idx != 0 && rules.m_emptyBaseClassOptimization == 0) {
                offset = 1;
            }
            int a = getLayoutAlignment(m, m.m_type, rules.m_bytesInPointer);
            if (isPointerType(m)) {
                a = rules.m_bytesInPointer;
            }
            if (maxAlign < a) {
                maxAlign = a;
            }
            int rem = offset - (offset / a) * a;
            if (rem != 0) {
                offset = offset - rem + a;
            }
            m.m_offset = (u16)offset;
            offset += computeMemberSize(m, rules, m.m_type);
        }
        int size = offset;
        int rem = offset - (offset / maxAlign) * maxAlign;
        if (rem != 0) {
            size = offset - rem + maxAlign;
        }
        c->setObjectSize(size != 0 ? size : 1);
        if (rules.m_reusePaddingOptimization == 0) {
            offset = size;
        }
        byteIdx += 4;
        idx++;
    }
}

void hkStructureLayout::computeMemberOffsetsInplace(hkClass* klass, hkPointerMapBase<hkUlong>& done) {
    if (!hkPointerMapHasKey(done, (hkUlong)klass)) {
        retargetClassInplace(klass, m_rules, done);
    }
}
