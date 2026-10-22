#pragma once

#include <StaticAssert.h>
#include <so/event/so_event_presenter.h>
#include <so/collision/so_collision_log.h>
#include <so/so_instance_unit.h>
#include <types.h>

class soModuleAccesser;

class soCollisionAttackEventObserver : public soEventObserver<soCollisionAttackEventObserver> {
public:
    typedef u16 AttributeMask;
    static const AttributeMask ATTRIBUTE_MASK_NONE = 0;
    struct AttributeFlag {
        union {
            struct {
                bool : 1;
                bool : 1;
                bool : 1;
                bool : 1;
                bool : 1;
                bool : 1;
                bool : 1;
                bool : 1;
                bool : 1;
                bool : 1;
                bool : 1;
                bool : 1;
                bool : 1;
                bool : 1;
                bool : 1;
                bool : 1;
            };
            AttributeMask m_mask;
        };
        inline AttributeFlag() : m_mask(ATTRIBUTE_MASK_NONE) {}
        inline AttributeFlag(AttributeMask bits) : m_mask(bits) {}
        inline ~AttributeFlag() {}

        AttributeFlag(soAttributeFlag f) : m_mask(f.m_mask) { }
        operator soAttributeFlag() { return soAttributeFlag(m_mask); }
    };

    soCollisionAttackEventObserver(short unitID) : soEventObserver<soCollisionAttackEventObserver>(unitID) {};

    virtual void addObserver(short param1, s8 param2);
    virtual void notifyEventCollisionAttack(float power, soCollisionLog* collisionLog, soModuleAccesser* moduleAccesser);;
    virtual bool notifyEventCollisionAttackCheck(u32 flags);
};
static_assert(sizeof(soCollisionAttackEventObserver) == 12, "Class is wrong size!");
