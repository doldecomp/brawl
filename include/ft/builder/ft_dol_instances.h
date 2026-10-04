#pragma once

// Concrete template instantiations that live in sora_melee (the "DOL side") but are
// used by every fighter REL.  The fighter REL only calls them (bl to the sora_melee
// symbol), it never instantiates its own copy.  MWCC would instantiate the inline
// definitions from the BrawlHeaders, so we declare an explicit full specialization with
// the same layout, whose members are declared but never defined.
//
//   FT_DOL_ARRAY_VECTOR(T, C)   ->   soArrayVector<T, C>   (ctor(size, int), dtor)
//
// Do not instantiate the same (T, C) twice in one TU (compile error). Add new pairs to
// the module header that needs them (see ft/builder/*).

#include <so/so_array.h>
#include <types.h>

#define FT_DOL_ARRAY_VECTOR(T, C)                                                              \
    template <>                                                                                \
    class soArrayVector<T, C> : public soArrayVectorAbstract<T> {                              \
        s32 m_topIndex : sizeof(bit_width<C>) + 1;                                             \
        s32 m_lastIndex : sizeof(bit_width<C>) + 1;                                            \
        s32 m_size : sizeof(bit_width<C>) + 1;                                                 \
        u32 m_isFull : 1;                                                                      \
        T m_elements[C];                                                                       \
    public:                                                                                    \
        soArrayVector(s32 = 0);                                                                \
        soArrayVector(s32 size, s32);                                                           \
        soArrayVector(s32 size, const T& element, s32);                                        \
        virtual s32 size() const;                                                              \
        virtual ~soArrayVector();                                                              \
        virtual s32 capacity() const;                                                          \
        virtual bool isFull() const;                                                           \
        virtual T& atFastAbstractSub(s32 index) const;                                         \
        virtual T& getArrayValueConst(s32 index);                                              \
        virtual s32 getTopIndex() const;                                                       \
        virtual s32 getLastIndex() const;                                                      \
        virtual void setSize(s32 size);                                                        \
        virtual void setTopIndex(s32 topIndex);                                                \
        virtual void setLastIndex(s32 lastIndex);                                              \
        virtual void onFull();                                                                 \
        virtual void offFull();                                                                \
    }
