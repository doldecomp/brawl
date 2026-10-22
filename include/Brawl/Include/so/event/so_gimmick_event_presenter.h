#pragma once

#include <StaticAssert.h>
#include <so/collision/so_collision_attack_part.h>
#include <so/event/so_event_presenter.h>
#include <st/st_trigger_observe.h>
#include <types.h>

namespace Gimmick {
    enum EventKind {
        Barrel_Event_In = 0x2,
        Barrel_Event_Shoot_Trigger = 0x3,
        Barrel_Event_Shoot = 0x4,
        Barrel_Event_Set_Speed = 0x5,
        Barrel_Event_Set_Path = 0x6,
        Barrel_Event_End_Path = 0x7,
        Barrel_Event_Break = 0x8,
        Barrel_Event_Pos = 0x9,

        Catapult_Event_On = 0xC,
        Catapult_Event_Shoot = 0xD,
        Catapult_Event_Pos = 0xE,

        Door_Event_In = 0x11,

        Ladder_Event_Get_Info = 0x14,

        Spring_Event_On = 0x17,
        Spring_Event_Shoot = 0x18,
        Spring_Event_Pos = 0x19,

        Truck_Event_In = 0x1C,
        Truck_Event_Ride = 0x1D,
        Truck_Event_Exit = 0x1E,
        Truck_Event_Start_Run = 0x1F,
        Truck_Event_Pos = 0x20,
        Truck_Event_Crash = 0x21,

        Chappy_Event_In = 0x27,
        Chappy_Event_Pos = 0x28,

        Elevator_Event_On = 0x2b,
        Elevator_Event_Up = 0x2c,
        Elevator_Event_Down = 0x2d,

        Event_Boot = 0x32,
        Event_Exit = 0x33,
        Event_Disable = 0x34,
    };
}


struct soGimmickEventArgs {
    Gimmick::EventKind m_kind;
    int m_sendID;
protected:
    inline soGimmickEventArgs(Gimmick::EventKind kind, int sendID) : m_kind(kind), m_sendID(sendID) {}
};

struct soGimmickSpringEventArgs : soGimmickEventArgs {
    Vec3f m_topPos;
    float m_bounce;
    float m_rot;
protected:
    inline soGimmickSpringEventArgs(Gimmick::EventKind kind, int sendID) : soGimmickEventArgs(kind, sendID) {}
    inline soGimmickSpringEventArgs(Gimmick::EventKind kind, int sendID, Vec3f topPos, float bounce, float rot) : soGimmickEventArgs(kind, sendID), m_topPos(topPos), m_bounce(bounce), m_rot(rot) {}
    inline soGimmickSpringEventArgs(Gimmick::EventKind kind, int sendID, Vec3f topPos) : soGimmickEventArgs(kind, sendID), m_topPos(topPos) {}
};
struct soGimmickSpringEventArgs_On : soGimmickSpringEventArgs {
    inline soGimmickSpringEventArgs_On() : soGimmickSpringEventArgs(Gimmick::Spring_Event_On, 0) {}
};
struct soGimmickSpringEventArgs_Shoot : soGimmickSpringEventArgs {
    inline soGimmickSpringEventArgs_Shoot(Vec3f topPos, float bounce, float rot) : soGimmickSpringEventArgs(Gimmick::Spring_Event_Shoot, 0, topPos, bounce, rot) {}
};
struct soGimmickSpringEventArgs_Pos : soGimmickSpringEventArgs {
    inline soGimmickSpringEventArgs_Pos(Vec3f topPos) : soGimmickSpringEventArgs(Gimmick::Spring_Event_Pos, 0, topPos) {}
};

struct soGimmickLadderEventArgs : soGimmickEventArgs {
    Vec3f m_upperNodePos;
    Vec3f m_underNodePos;
    bool m_restrictUpExit;
    bool m_33;
protected:
    inline soGimmickLadderEventArgs(Gimmick::EventKind kind, int sendID) : soGimmickEventArgs(kind, sendID) {};
};
struct soGimmickLadderEventArgs_GetInfo : soGimmickLadderEventArgs {
    inline soGimmickLadderEventArgs_GetInfo() : soGimmickLadderEventArgs(Gimmick::Ladder_Event_Get_Info, 0) {};
};

struct soGimmickCatapultEventArgs : soGimmickEventArgs {
    Vec2f m_pos;
    float m_lr;
    float m_launchSpeed;
    float m_vector;
protected:
    inline soGimmickCatapultEventArgs(Gimmick::EventKind kind, int sendID) : soGimmickEventArgs(kind, sendID) {}
    inline soGimmickCatapultEventArgs(Gimmick::EventKind kind, int sendID, float launchSpeed, float vector) : soGimmickEventArgs(kind, sendID), m_launchSpeed(launchSpeed), m_vector(vector) {}
    inline soGimmickCatapultEventArgs(Gimmick::EventKind kind, int sendID, Vec2f pos, float lr) : soGimmickEventArgs(kind, sendID), m_pos(pos), m_lr(lr) {}
};
struct soGimmickCatapultEventArgs_On : soGimmickCatapultEventArgs {
    inline soGimmickCatapultEventArgs_On() : soGimmickCatapultEventArgs(Gimmick::Catapult_Event_On, 0) {}
};
struct soGimmickCatapultEventArgs_Shoot : soGimmickCatapultEventArgs {
    inline soGimmickCatapultEventArgs_Shoot(float launchSpeed, float vector) : soGimmickCatapultEventArgs(Gimmick::Catapult_Event_Shoot, 0, launchSpeed, vector) {};
};
struct soGimmickCatapultEventArgs_Pos : soGimmickCatapultEventArgs {
    inline soGimmickCatapultEventArgs_Pos(Vec2f pos, float lr) : soGimmickCatapultEventArgs(Gimmick::Catapult_Event_Pos, 0, pos, lr) {};
};

struct soGimmickDoorEventArgs : soGimmickEventArgs {
    Vec3f m_pos;
    bool m_noInto;
protected:
    inline soGimmickDoorEventArgs(Gimmick::EventKind kind, int sendID) : soGimmickEventArgs(kind, sendID) {};
};
struct soGimmickDoorEventArgs_In : soGimmickDoorEventArgs {
    inline soGimmickDoorEventArgs_In() : soGimmickDoorEventArgs(Gimmick::Door_Event_In, 0) {};
};

struct soGimmickBarrelEventArgs : soGimmickEventArgs {
    Vec3f m_pos;
    unsigned int m_breakHitstopFrame;
    soCollisionAttackData* m_attackData;
    float m_shootSpeed;
    float m_rot;
    float m_shootTimerSpeed;
    float m_shootAngleOffset;
    float m_shootFallSpeed;
protected:
    inline soGimmickBarrelEventArgs(Gimmick::EventKind kind, int sendID) : soGimmickEventArgs(kind, sendID) {};
    inline soGimmickBarrelEventArgs(Gimmick::EventKind kind, int sendID, Vec3f pos, soCollisionAttackData* attackData) : soGimmickEventArgs(kind, sendID), m_pos(pos), m_attackData(attackData) {};
    inline soGimmickBarrelEventArgs(Gimmick::EventKind kind, int sendID, Vec3f pos, soCollisionAttackData* attackData, float rot) : soGimmickEventArgs(kind, sendID), m_pos(pos), m_attackData(attackData), m_rot(rot) {};
    inline soGimmickBarrelEventArgs(Gimmick::EventKind kind, int sendID, Vec3f pos, soCollisionAttackData* attackData, float rot, float shootSpeed, float shootTimerSpeed, float shootAngleoffset, float shootStunTimerSpeed) : soGimmickEventArgs(kind, sendID), m_pos(pos), m_attackData(attackData), m_rot(rot), m_shootSpeed(shootSpeed), m_shootTimerSpeed(shootTimerSpeed), m_shootAngleOffset(shootAngleoffset), m_shootFallSpeed(shootStunTimerSpeed) {};
};
struct soGimmickBarrelEventArgs_In : soGimmickBarrelEventArgs {
    inline soGimmickBarrelEventArgs_In() : soGimmickBarrelEventArgs(Gimmick::Barrel_Event_In, 0, Vec3f(0.0, 0.0, 0.0), NULL) {};
};
struct soGimmickBarrelEventArgs_ShootTrigger : soGimmickBarrelEventArgs {
    inline soGimmickBarrelEventArgs_ShootTrigger() : soGimmickBarrelEventArgs(Gimmick::Barrel_Event_Shoot_Trigger, 0, Vec3f(0.0, 0.0, 0.0), NULL) {};
};
struct soGimmickBarrelEventArgs_Shoot: soGimmickBarrelEventArgs {
    //inline soGimmickBarrelEventArgs_Shoot() : soGimmickBarrelEventArgs(Gimmick::Barrel_Event_Shoot, 0, Vec3f(0.0, 0.0, 0.0), NULL) {};
    inline soGimmickBarrelEventArgs_Shoot(Vec3f pos, soCollisionAttackData* attackData, float rot) : soGimmickBarrelEventArgs(Gimmick::Barrel_Event_Shoot, 0, pos, attackData, rot) {};
};
struct soGimmickBarrelEventArgs_SetSpeed : soGimmickBarrelEventArgs {
    //inline soGimmickBarrelEventArgs_SetSpeed() : soGimmickBarrelEventArgs(Gimmick::Barrel_Event_Set_Speed, 0, Vec3f(0.0, 0.0, 0.0), NULL) {};
    inline soGimmickBarrelEventArgs_SetSpeed(float rot, float shootSpeed, float shootTimerSpeed, float shootAngleOffset, float shootStunTimerSpeed) : soGimmickBarrelEventArgs(Gimmick::Barrel_Event_Set_Speed, 0, Vec3f(0.0, 0.0, 0.0), NULL, rot, shootSpeed, shootTimerSpeed, shootAngleOffset, shootStunTimerSpeed) {};
};
struct soGimmickBarrelEventArgs_SetPath : soGimmickBarrelEventArgs {
    inline soGimmickBarrelEventArgs_SetPath(Vec3f pos) : soGimmickBarrelEventArgs(Gimmick::Barrel_Event_Set_Path, 0, pos, NULL) {};
};
struct soGimmickBarrelEventArgs_EndPath : soGimmickBarrelEventArgs {
    inline soGimmickBarrelEventArgs_EndPath() : soGimmickBarrelEventArgs(Gimmick::Barrel_Event_End_Path, 0, Vec3f(0.0, 0.0, 0.0), NULL) {};
};
struct soGimmickBarrelEventArgs_Break : soGimmickBarrelEventArgs {
    inline soGimmickBarrelEventArgs_Break() : soGimmickBarrelEventArgs(Gimmick::Barrel_Event_Break, 0, Vec3f(0.0, 0.0, 0.0), NULL) {};
};
struct soGimmickBarrelEventArgs_Pos : soGimmickBarrelEventArgs {
    inline soGimmickBarrelEventArgs_Pos(Vec3f pos) : soGimmickBarrelEventArgs(Gimmick::Barrel_Event_Pos, 0, pos, NULL) {};
};

struct soGimmickElevatorEventArgs_On : soGimmickEventArgs {
    bool m_canGoUp;
    bool m_canGoDown;
    inline soGimmickElevatorEventArgs_On() : soGimmickEventArgs(Gimmick::Elevator_Event_On, 0), m_canGoUp(false), m_canGoDown(false) {};
};
struct soGimmickElevatorEventArgs_Up : soGimmickEventArgs {
    inline soGimmickElevatorEventArgs_Up() : soGimmickEventArgs(Gimmick::Elevator_Event_Up, 0) {};
};
struct soGimmickElevatorEventArgs_Down : soGimmickEventArgs {
    inline soGimmickElevatorEventArgs_Down() : soGimmickEventArgs(Gimmick::Elevator_Event_Down, 0) {};
};

struct soGimmickTruckEventArgs : soGimmickEventArgs {
    Vec3f m_pos;
    Vec2f m_stick;
protected:
    inline soGimmickTruckEventArgs(Gimmick::EventKind eventKind, int sendID, Vec3f pos) : soGimmickEventArgs(eventKind, sendID), m_pos(pos) {};
    inline soGimmickTruckEventArgs(Gimmick::EventKind eventKind, int sendID, Vec3f pos, Vec2f stick) : soGimmickEventArgs(eventKind, sendID), m_pos(pos), m_stick(stick) {};
};
struct soGimmickTruckEventArgs_In : soGimmickTruckEventArgs {
    inline soGimmickTruckEventArgs_In(Vec3f pos) : soGimmickTruckEventArgs(Gimmick::Truck_Event_In, 0, pos) {};
};
struct soGimmickTruckEventArgs_Ride : soGimmickTruckEventArgs {
    inline soGimmickTruckEventArgs_Ride(Vec2f stick) : soGimmickTruckEventArgs(Gimmick::Truck_Event_Ride, 0, Vec3f(0, 0, 0), stick) {};
};
struct soGimmickTruckEventArgs_Exit : soGimmickTruckEventArgs {
    inline soGimmickTruckEventArgs_Exit() : soGimmickTruckEventArgs(Gimmick::Truck_Event_Exit, 0, Vec3f(0, 0, 0)) {};
};
struct soGimmickTruckEventArgs_StartRun : soGimmickTruckEventArgs {
    inline soGimmickTruckEventArgs_StartRun() : soGimmickTruckEventArgs(Gimmick::Truck_Event_Start_Run, 0, Vec3f(0, 0, 0)) {};
};
struct soGimmickTruckEventArgs_Pos : soGimmickTruckEventArgs {
    inline soGimmickTruckEventArgs_Pos(Vec3f pos) : soGimmickTruckEventArgs(Gimmick::Truck_Event_Pos, 0, pos) {};
};
struct soGimmickTruckEventArgs_Crash : soGimmickTruckEventArgs {
    inline soGimmickTruckEventArgs_Crash() :  soGimmickTruckEventArgs(Gimmick::Truck_Event_Crash, 0, Vec3f(0, 0, 0)) {};
};

struct soGimmickChappyEventArgs : soGimmickEventArgs {
    Vec3f m_pos;
protected:
    inline soGimmickChappyEventArgs(Gimmick::EventKind eventKind, int sendID) : soGimmickEventArgs(eventKind, sendID) {};
    inline soGimmickChappyEventArgs(Gimmick::EventKind eventKind, int sendID, Vec3f pos) : soGimmickEventArgs(eventKind, sendID), m_pos(pos) {};
};
struct soGimmickChappyEventArgs_In : soGimmickChappyEventArgs {
    inline soGimmickChappyEventArgs_In() : soGimmickChappyEventArgs(Gimmick::Chappy_Event_In, 0) {};
};
struct soGimmickChappyEventArgs_Pos : soGimmickChappyEventArgs {
    inline soGimmickChappyEventArgs_Pos(Vec3f pos) : soGimmickChappyEventArgs(Gimmick::Chappy_Event_Pos, 0, pos) {};
};

struct soGimmickEventArgs_Exit : soGimmickEventArgs {
    inline soGimmickEventArgs_Exit() : soGimmickEventArgs(Gimmick::Event_Exit, 0) {}
};
struct soGimmickEventArgs_Boot : soGimmickEventArgs {
    inline soGimmickEventArgs_Boot() : soGimmickEventArgs(Gimmick::Event_Boot, 0) {}
};
struct soGimmickEventArgs_Disable : soGimmickEventArgs {
    inline soGimmickEventArgs_Disable() : soGimmickEventArgs(Gimmick::Event_Disable, 0) {}
};

class soGimmickEventObserver : public soEventObserver<soGimmickEventObserver> {
public:
    soGimmickEventObserver() : soEventObserver<soGimmickEventObserver>(0x3) {};
    soGimmickEventObserver(short unitID) : soEventObserver<soGimmickEventObserver>(unitID) {};
    soGimmickEventObserver(short param1, s8 param2);

    virtual void addObserver(short param1, s8 param2);
    virtual void notifyEventGimmick(soGimmickEventArgs* eventInfo, int* taskId);
};
static_assert(sizeof(soGimmickEventObserver) == 12, "Class is wrong size!");

