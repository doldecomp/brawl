#pragma once

#include <StaticAssert.h>
#include <so/so_null.h>
#include <types.h>

class soModuleAccesser;

class soItemSearch : public soNull, public soNullable {
public:
    virtual ~soItemSearch();
    virtual bool search(int*, u32, soModuleAccesser*);

};
static_assert(sizeof(soItemSearch) == 12, "Class is wrong size!");

class soItemSearchImpl : public soItemSearch {
public:
    virtual ~soItemSearchImpl();
    virtual bool search(int* areaId, u32, soModuleAccesser*);

};
static_assert(sizeof(soItemSearchImpl) == 12, "Class is wrong size!");