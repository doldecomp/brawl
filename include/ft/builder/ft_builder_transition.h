#pragma once

// soTransitionModuleBuilder<soTransitionModuleBuildConfig<TypeList>>: the transition term groups of a status/motion module.
// Layout (status builder, 20 groups): soArrayVector<soTransitionTermGroup, N> (+0), the soJagArray of term arrays
// (a linear hierarchy with one soArrayVector<soInstanceUnitFullProperty<soTransitionTerm>, K> per type list entry,
// the last entry of the list comes first in memory) and the soTransitionModuleImpl.

#include <ft/builder/ft_dol_array_list.h>
#include <so/transition/so_transition_module_impl.h>
#include <types.h>

template <class H, class T>
struct soTypeList {
    typedef H Head;
    typedef T Tail;
};
struct soTypeListNullType { };

template <int N>
struct soIntToType {
    enum { value = N };
};

template <class TL>
struct soTypeListLength;
template <>
struct soTypeListLength<soTypeListNullType> {
    enum { value = 0 };
};
template <class H, class T>
struct soTypeListLength<soTypeList<H, T> > {
    enum { value = 1 + soTypeListLength<T>::value };
};

template <class T>
class soArrayPoolRoot {
public:
    typedef T ElementType;
    enum { Depth = 0 };
    soArray<T>* getArray(int index, int total) { return 0; }
};

template <class N, class Base>
class soArrayPool : public Base {
    soArrayVector<typename Base::ElementType, N::value> m_array;
public:
    enum { Depth = Base::Depth + 1 };
    soArrayPool() : m_array(0) { }
    soArray<typename Base::ElementType>* getArray(int index, int total) {
        if (index == total - Depth) {
            return &m_array;
        }
        return Base::getArray(index, total);
    }
};

template <class TL, template <class, class> class Unit, class Root>
class soLineHierarchy;

template <class H, class T, template <class, class> class Unit, class Root>
class soLineHierarchy<soTypeList<H, T>, Unit, Root> : public Unit<H, soLineHierarchy<T, Unit, Root> > {
public:
    ~soLineHierarchy() { }
};

template <class H, template <class, class> class Unit, class Root>
class soLineHierarchy<soTypeList<H, soTypeListNullType>, Unit, Root> : public Unit<H, Root> {
public:
    ~soLineHierarchy() { }
};

template <class T, class TL>
class soJagArray : public soLineHierarchy<TL, soArrayPool, soArrayPoolRoot<T> > {
public:
    enum { Length = soTypeListLength<TL>::value };
    soArray<T>* getArrayAt(int index) {
        return this->getArray(index, (int)Length);
    }
};

template <class TL>
class soTransitionModuleBuildConfig {
public:
    typedef TL TypeList;
    enum { GroupCount = soTypeListLength<TL>::value };
};

template <class BC>
class soTransitionModuleBuilder {
    soArrayVector<soTransitionTermGroup, BC::GroupCount> m_groups;
    soJagArray<soInstanceUnitFullProperty<soTransitionTerm>, typename BC::TypeList> m_termArrays;
    soTransitionModuleImpl m_module;
public:
    soTransitionModuleBuilder() : m_groups(0), m_termArrays(), m_module(&m_groups) {
        for (int i = 0; i < BC::GroupCount; i++) {
            soTransitionTermGroup group(m_termArrays.getArrayAt(i));
            soArray<soTransitionTermGroup>* groups = &m_groups;
            groups->push(group);
        }
    }
    soTransitionModule* getModule() { return &m_module; }
};

// The type list of the status module of every fighter (term counts of the 20 groups, in group order).
typedef soTypeList<soIntToType<25>, soTypeList<soIntToType<6>, soTypeList<soIntToType<2>, soTypeList<soIntToType<1>,
        soTypeList<soIntToType<17>, soTypeList<soIntToType<3>, soTypeList<soIntToType<1>, soTypeList<soIntToType<2>,
        soTypeList<soIntToType<8>, soTypeList<soIntToType<2>, soTypeList<soIntToType<1>, soTypeList<soIntToType<6>,
        soTypeList<soIntToType<3>, soTypeList<soIntToType<1>, soTypeList<soIntToType<1>, soTypeList<soIntToType<2>,
        soTypeList<soIntToType<3>, soTypeList<soIntToType<2>, soTypeList<soIntToType<6>, soTypeList<soIntToType<1>,
        soTypeListNullType> > > > > > > > > > > > > > > > > > > > ftStatusTransitionTypeList;
