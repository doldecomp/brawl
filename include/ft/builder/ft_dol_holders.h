#pragma once

// soArraySelectHolder<1, soArrayVector<T, N>, ...>: wrapper of an array with an out-of-line destructor in the fighter
// RELs. Used by the module builders (as a member, or as the first base class where the destructor is inlined).

#include <ft/builder/ft_dol_array_list.h>
#include <types.h>

template <s32 I, typename V, typename Null>
class soArraySelectHolder {
public:
    V m_array;
    soArraySelectHolder() : m_array(0) { }
    soArraySelectHolder(s32 size, s32 unk) : m_array(size, unk) { }
    explicit soArraySelectHolder(s32 size) : m_array(size) { }
    ~soArraySelectHolder() { }
    V* get() { return &m_array; }
};
