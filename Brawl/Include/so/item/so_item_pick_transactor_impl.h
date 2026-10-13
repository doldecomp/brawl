#pragma once

#include <StaticAssert.h>
#include <so/so_null.h>
#include <it/it_archive.h>
#include <so/item/so_item_search_impl.h>
#include <types.h>

class soModuleAccesser;

struct soItemInfo {
    itKind m_kind;
    BaseItem* m_item;
    itParam::TraitFlag m_trait;
    itParam::SizeKind m_size;
    bool m_isVisible : 1;
    bool m_isHoldAnim : 1;
    itParam::AttachGroup m_attachGroup : 6;
    char _0x11[3];
};
static_assert(sizeof(soItemInfo) == 0x14, "Class is wrong size!");

class soItemPickTransactor : public soNull, public soNullable {
public:
    virtual ~soItemPickTransactor();
    virtual bool check(soItemSearch*, soItemInfo*, soModuleAccesser*);
    virtual bool pickup(soItemSearch*, soModuleAccesser*, u8, itParam::TraitMask, u32, u32 index);
};
static_assert(sizeof(soItemPickTransactor) == 12, "Class is wrong size!");

class soItemPickTransactorImpl : public soItemPickTransactor {
public:
    virtual ~soItemPickTransactorImpl();
    virtual bool check(soItemSearch*, soItemInfo*, soModuleAccesser*);
    virtual bool pickup(soItemSearch*, soModuleAccesser*, u8, itParam::TraitMask, u32, u32 index);
};
static_assert(sizeof(soItemPickTransactorImpl) == 12, "Class is wrong size!");