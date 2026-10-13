#pragma once

#include <StaticAssert.h>
#include <ft/ft_entry.h>
#include <so/so_null.h>
#include <types.h>

class ftClassInfo : private soNull, public soNullable {
public:
    ftClassInfo(bool isNull = false);

    virtual ~ftClassInfo();
    virtual ftClassInfo* create() const = 0;

    void setClassInfo(ftKind kind, ftClassInfo* info);
    static ftClassInfo* getClassInfo(ftKind kind);
};
static_assert(sizeof(ftClassInfo) == 0xC, "Class is the wrong size!");

class ftClassInfoNull : public ftClassInfo {
public:
    ftClassInfoNull() : ftClassInfo(true) { }

    virtual ~ftClassInfoNull();
    virtual ftClassInfo* create() const;
};
static_assert(sizeof(ftClassInfoNull) == 0xC, "Class is the wrong size!");

extern ftClassInfoNull g_ftClassInfoNull;
