#pragma once

#include <StaticAssert.h>
#include <em/em_create.h>
#include <em/resource/em_resource_module_impl.h>
#include <em/enemy.h>
#include <so/so_info.h>
#include <types.h>

class emInfo : public soInfo {
public:
    typedef Enemy* (*CreateEnemyFunc_t)(u32, emCreate*);
    typedef void (*ModifyExParamFunc_t)(emResourceModuleImpl* p1, emCreate const* p2);
    typedef void (*DeleteExParamFunc_t)(emResourceModuleImpl* p1);
    static const s32 NumEnemies = 61;
private:
    static const u32 NodeNumTable[NumEnemies];
    static const u32 MotionNumTable[NumEnemies];
    static const u32 StatusNumTable[NumEnemies];
    static const u32 KineticEnergyNumTable[NumEnemies];
    static const u32 KineticEnergyParamAryPtrGetIdTable[NumEnemies];
    static const u32 AreaNumTable[NumEnemies];
    static const u32 AreaParamAryPtrGetIdTable[NumEnemies];
    static const u32 TargetSearchNumTable[NumEnemies];
    static const u32 TargetSearchParamAryPtrGetIdTable[NumEnemies];
    static const u32 AINumTable[NumEnemies];
    static const u32 SEIdTable[NumEnemies];
    static const u32 StandByStatusKindTable[NumEnemies];
public:
    static CreateEnemyFunc_t CreateFuncPtrTable[NumEnemies];
    static ModifyExParamFunc_t ModifyExParamFuncPtrTable[NumEnemies];
    static DeleteExParamFunc_t DeleteExParamFuncPtrTable[NumEnemies];

    static emInfo* getInstance();

    emInfo();
    virtual ~emInfo();
    virtual bool isInvalidKind(int kind);
    virtual int getInvalidKind();
    virtual const char* getNamePtr(int kind);
    virtual u32 getMotionNum(int kind);
    virtual u32 getStatusNum(int kind);
    u32 isPrimKind(EnemyKind kind);
    u32 getNodeNum(EnemyKind kind);
    u32 getKineticEnergyNum(EnemyKind kind);
    u32 getKineticEnergyParamAryPtrGetId(EnemyKind kind);
    u32 getAreaNum(EnemyKind kind);
    u32 getAreaParamAryPtrGetId(EnemyKind kind);
    u32 getTargetSearchNum(EnemyKind kind);
    u32 getTargetSearchParamAryPtrGetId(EnemyKind kind);
    u32 getAINum(EnemyKind kind);
    CreateEnemyFunc_t getCreateFuncPtr(EnemyKind kind);
    ModifyExParamFunc_t getExParamModifyFuncPtr(EnemyKind kind);
    DeleteExParamFunc_t getExParamDeleteFuncPtr(EnemyKind kind);
    u32 getSEId(EnemyKind kind);
    u32 StandByStatusKind(EnemyKind kind);
};
static_assert(sizeof(emInfo) == 0x4, "Class has the wrong size!");
