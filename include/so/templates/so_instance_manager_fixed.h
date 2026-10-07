#pragma once
// Local copy of the BrawlHeaders fixed-manager interface for isolated member emission.
#include <so/so_null.h>
template <class T>
class soInstanceManagerFixed : public soNullable {
public:
    virtual T& at(s32 index) = 0;
    virtual T& atIndex(s32 index) = 0;
    virtual s32 getId(s32 index) = 0;
    virtual u32 size() const = 0;
    virtual bool isEmpty() const;
    virtual bool isContain(s32) const = 0;
};

// MATCH-ONLY: Preserve the separately owned emptiness query.
#ifndef SO_INSTANCE_MANAGER_EXTERNAL_FIXED_IS_EMPTY
template<class T>
bool soInstanceManagerFixed<T>::isEmpty() const { return size() == 0; }
#endif
