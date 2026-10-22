#pragma once

#include <StaticAssert.h>
#include <so/so_instance_unit.h>
#include <so/so_null.h>
#include <so/so_enable.h>
#include <so/so_suspend.h>
#include <mt/mt_vector.h>
#include <climits>

class soModuleAccesser;

class soKineticEnergy : public soNullable, public soEnable, public soSuspendable {
public:
    enum Attribute {
        Attribute_Main = 0x0,
        Attribute_Damage = 0x1,
        Attribute_Extern = 0x2,
        Attribute_Ground = 0x3,
        Attribute_Extern2 = 0x4,
    };
    typedef u16 AttributeMask;
    static const AttributeMask ATTRIBUTE_MASK_NONE = 0;
    static const AttributeMask ATTRIBUTE_MASK_MAIN = 1 << Attribute_Main;
    static const AttributeMask ATTRIBUTE_MASK_DAMAGE = 1 << Attribute_Damage;
    static const AttributeMask ATTRIBUTE_MASK_EXTERN = 1 << Attribute_Extern;
    static const AttributeMask ATTRIBUTE_MASK_GROUND = 1 << Attribute_Ground;
    static const AttributeMask ATTRIBUTE_MASK_EXTERN2 = 1 << Attribute_Extern2;
    static const AttributeMask ATTRIBUTE_MASK_ALL = USHRT_MAX;
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
                bool m_extern2 : 1;
                bool m_ground : 1;
                bool m_extern : 1;
                bool m_damage: 1;
                bool m_main : 1;
            };
            AttributeMask m_mask;
        };
        inline AttributeFlag() : m_mask(ATTRIBUTE_MASK_NONE) {}
        inline AttributeFlag(AttributeMask bits) : m_mask(bits) {}
        inline ~AttributeFlag() {}

        AttributeFlag(soAttributeFlag f) : m_mask(f.m_mask) { }
        operator soAttributeFlag() { return soAttributeFlag(m_mask); }
    };

    enum OutsideType {
        Outside_None = -1,
        Outside_Movement_Ground = 0x0,
        Outside_Wind = 0x1,
        Outside_Attack = 0x2,
        Outside_Damage_Reserved = 0x3
    };

    virtual void updateEnergy(soModuleAccesser* moduleAccesser);
    virtual Vec2f getSpeed();
    virtual Vec3f getSpeed3f();
    virtual Vec3f getRotation();
    virtual void resetEnergy(int, Vec2f*, Vec3f*, soModuleAccesser* moduleAccesser);
    virtual void clearSpeed();
    virtual void clearRotSpeed();
    virtual void mulSpeed(Vec3f* speed);
    virtual void mulAccel(Vec3f* accel);
    virtual void reflectSpeed(Vec3f* speed);
    virtual void reflectAccel(Vec3f* accel);
    virtual void onConsiderGroundFriction();
    virtual void offConsiderGroundFriction();
    virtual ~soKineticEnergy();
};
static_assert(sizeof(soKineticEnergy) == 8, "Class is wrong size!");
