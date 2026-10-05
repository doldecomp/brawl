#pragma once

#include <StaticAssert.h>
#include <so/so_null.h>
#include <types.h>

class ftVirtualNodeMatrixPool : public soNullable {
public:
    ftVirtualNodeMatrixPool(bool isNull) : soNullable(isNull) { }
    virtual ~ftVirtualNodeMatrixPool() = 0;
    virtual void* getHitMatrix() = 0;
    virtual void* getCommonMatrix() = 0;
    virtual void* getExtendMatrix() = 0;
};
static_assert(sizeof(ftVirtualNodeMatrixPool) == 0x8, "Class is the wrong size!");

class ftVirtualNodeMatrixPoolImpl : public ftVirtualNodeMatrixPool {
    // TODO types of data members and return types of member functions
    // HYPOTHESIS: arrays of floats (4 byte alignment), so that the matrices start at +0x8 and not directly behind the 5 bytes of the base
    float m_hitMatrix[0xF0];
    float m_commonMatrix[0x24];
    float m_extendMatrix[0x18];
public:
    ftVirtualNodeMatrixPoolImpl() : ftVirtualNodeMatrixPool(false) { }
    virtual ~ftVirtualNodeMatrixPoolImpl() { }
    virtual void* getHitMatrix() { return &m_hitMatrix; }
    virtual void* getCommonMatrix() { return &m_commonMatrix; }
    virtual void* getExtendMatrix() { return &m_extendMatrix; }
};
static_assert(sizeof(ftVirtualNodeMatrixPoolImpl) == 0x4B8, "Class is the wrong size!");

class ftVirtualNodeMatrixPoolNull : public ftVirtualNodeMatrixPool {
public:
    ftVirtualNodeMatrixPoolNull() : ftVirtualNodeMatrixPool(true) { }
    virtual ~ftVirtualNodeMatrixPoolNull() { }
    virtual void* getHitMatrix() { return nullptr; }
    virtual void* getCommonMatrix() { return nullptr; }
    virtual void* getExtendMatrix() { return nullptr; }
};
static_assert(sizeof(ftVirtualNodeMatrixPoolNull) == 0x8, "Class is the wrong size!");
