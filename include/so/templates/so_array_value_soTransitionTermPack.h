#pragma once
#include <StaticAssert.h>
#include <so/so_array.h>

// HYPOTHESIS: identifier plus a contractible term table; copy view only.
struct soTransitionTermPack {
    u32 unk0;
    class TermTable : public soArrayContractible<s32>, public soConnectable<TermTable> {
        s32* m_elements;
        s32 m_size;
    public:
        virtual bool isNull() const;
        virtual s32& at(s32);
        virtual const s32& at(s32) const;
        virtual s32 size() const;
        virtual void shift();
        virtual void pop();
        virtual void clear();
        virtual ~TermTable();
        TermTable& operator=(const TermTable& other) {
            if (this == &other)
                return *this;
            // MATCH-ONLY: retain the nested self-assignment guard in the copy.
            if (this != &other) {
                soConnectable<TermTable>::operator=(other);
                const bool noElements = other.m_elements == nullptr;
                m_elements = other.m_elements;
                m_size = other.m_size;
                if (noElements)
                    m_size = 0;
            }
            return *this;
        }
    } unk4;
};
static_assert(sizeof(soTransitionTermPack) == 20, "Class is wrong size!");
