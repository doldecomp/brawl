#pragma once

#include <so/status/so_status_module_impl.h>
#include <types.h>

class soModuleAccesser;

// Per-fighter glide parameters (Meta Knight / Pit / Charizard), read with
// soValueAccesser::getConstantIndefinite(moduleAccesser, 0xa80b, 0). Field names are HYPOTHESES
// derived from how the glide status uses them (and from the Ultimate port's GlideParams names).
// Angles are in degrees, positive = nose up; speeds are per frame.
struct ftGlideParam {
    float m_angleMax;           // +0x00 upper clamp of the glide angle
    float m_angleMin;           // +0x04 lower clamp of the glide angle
    float unk08;                // +0x08
    float unk0c;                // +0x0c
    float unk10;                // +0x10
    float m_baseSpeed;          // +0x14 initial glide power
    float m_speedChange;        // +0x18 power lost per 90 degrees of climb
    float m_maxSpeed;           // +0x1c limit of the glide velocity
    float m_minSpeed;           // +0x20 below this velocity the glide stalls
    float m_gravityAccel;       // +0x24 growth of the gravity pull per frame
    float m_gravitySpeed;       // +0x28 limit of the gravity pull
    float m_stallRecoverAngle;  // +0x2c angle under which a stalled glide may recover
    float m_angleMoreSpeed;     // +0x30 below this angle the glide gains extra power
    float m_downSpeedAdd;       // +0x34 extra power gained when diving
    float unk38;                // +0x38
    float m_radialStick;        // +0x3c stick magnitude needed to steer
    float m_upAngleAccel;       // +0x40 angle speed gained per frame while pulling up
    float m_downAngleAccel;     // +0x44 angle speed gained per frame while pushing down
    float m_maxAngleSpeed;      // +0x48 limit of the angle speed
    float m_stallAngleAccel;    // +0x4c angle speed gained per frame while stalled and the stick is idle
    int m_wingBlend;            // +0x50 passed to addPartialAnimChr for the wing animation
};

// Status process for the glide (Glide, status 0x85) shared by Meta Knight, Pit and Charizard.
class ftStatusUniqProcessGlide : public soStatusUniqProcess {
public:
    virtual ~ftStatusUniqProcessGlide() { }
    virtual void initStatus(soModuleAccesser* moduleAccesser);
    virtual void exitStatus(soModuleAccesser* moduleAccesser, int);
    virtual void execStatus(soModuleAccesser* moduleAccesser);
    virtual void execFixPos(soModuleAccesser* moduleAccesser);
};
