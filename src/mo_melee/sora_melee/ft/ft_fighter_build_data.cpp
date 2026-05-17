#include <ft/ft_common_data_accesser.h>
#include <ft/ft_entry.h>
#include <ft/ft_fighter_build_data.h>
#include <ft/ft_manager.h>
#include <ft/ft_sound_id_exchanger_impl.h>
#include <mt/mt_vector.h>
#include <so/ground/so_ground_module_impl.h>
#include <so/kinetic/so_kinetic_energy.h>
#include <so/so_common_data_accesser.h>
#include <so/so_module_accesser_build_data.h>
#include <so/so_module_accesser.h>
#include <so/so_value_accesser.h>
#include <sr/sr_common.h>
#include <types.h>

class ftGroundConditionCheckerImpl : public soGroundConditionChecker {
public:
    virtual ~ftGroundConditionCheckerImpl();
    virtual bool isConditionNoCliffStop(soModuleAccesser* moduleAccesser);
};

static ftGroundConditionCheckerImpl g_ftGroundConditionCheckerImpl;

ftFighterBuildData::ftFighterBuildData(s32 entryId, ftKind kind,
                                       Heaps::HeapType instHeap,
                                       Heaps::HeapType nwModelInstHeap,
                                       Heaps::HeapType nwMotionInstHeap,
                                       s8 resGroupNo, soModuleAccesser* acc,
                                       s32 team, void* cameraRangeSet,
                                       void* cameraClipSphereSet) :
    m_entryId(entryId),
    m_kind(kind),
    m_ftData(g_ftCommonDataAccesser.getData(kind)),
    m_resGroupNo(resGroupNo),
    m_team(team),
    m_moduleAccsr(acc),
    m_cameraRangeSet(cameraRangeSet),
    m_cameraClipSphereSet(cameraClipSphereSet),
    m_instHeap(instHeap),
    m_nwModelInstHeap(nwModelInstHeap),
    m_nwMotionInstHeap(nwMotionInstHeap) { }

void* ftFighterBuildData::getAnimCmdData(u32 eventThread, s32 p2) {
    if (p2 == 0) {
        switch (eventThread) {
            case 0:
                return g_ftCommonData.dataCommon->commonActionEntryScripts;
            case 1:
            case 5:
                return m_ftData->unk30;
            case 2:
            case 6:
                return m_ftData->unk34;
            case 4:
            case 8:
                return m_ftData->unk3C;
            case 3:
            case 7:
                return m_ftData->unk38;
            case 10:
                return g_ftCommonData.dataCommon->flashOverlayScripts;
            default:
                goto Exit;
        }
    }
    if (p2 == 1 && eventThread == 0)
        return g_ftCommonData.dataCommon->commonActionExitScripts;
Exit:
    return nullptr;
}

soAnimCmdDisguiseList* ftFighterBuildData::getAnimCmdDisguiseList(bool p1, s32 actionType) {
    if (p1 == false) {
        if (actionType == 0)
            return m_ftData->unk50;
        if (actionType == 1)
            return m_ftData->unk54;
    }
    return nullptr;
}

u32 ftFighterBuildData::getMdlResId() {
    return 0xFFFF;
}

u32 ftFighterBuildData::getAnimResId() {
    return 0xFFFF;
}

u8 ftFighterBuildData::getResGroupNo() {
    return m_resGroupNo;
}

ftMotionData* ftFighterBuildData::getMotionData() {
    return g_ftCommonDataAccesser.getData(m_kind)->motionData;
}

ftStatusData* ftFighterBuildData::getStatusData() {
    return g_ftCommonDataAccesser.getData(m_kind)->statusData;
}

ftVisibilityData* ftFighterBuildData::getVisibilityData() {
    return g_ftCommonDataAccesser.getData(m_kind)->visibilityData;
}

soParamAccesser* ftFighterBuildData::getParamAccesser() {
    return &g_soParamAccesserNull;
}

s32 ftFighterBuildData::getAreaCategory() {
    return 0;
}

void* ftFighterBuildData::getCameraRangeSet() {
    return m_cameraRangeSet;
}

void* ftFighterBuildData::getCameraClipSphereSet() {
    return m_cameraClipSphereSet;
}

void* ftFighterBuildData::getItemNodeData() {
    return soValueAccesser::getConstantIndefinite(m_moduleAccsr, 43015, 0);
}

void* ftFighterBuildData::getModelExtendNodeTable() {
    return soValueAccesser::getConstantIndefinite(m_moduleAccsr, 43014, 0);
}

ftIkData* ftFighterBuildData::getIkData() {
    return g_ftCommonData.dataCommon->ikData;
}

ftShakeData* ftFighterBuildData::getShakeData() {
    return g_ftCommonData.dataCommon->shakeData;
}

void* ftFighterBuildData::getEffectNodeData() {
    return nullptr;
}

void* ftFighterBuildData::getEffectEmitData() {
    return soValueAccesser::getConstantIndefinite(m_moduleAccsr, 43010, 0);
}

ftEffectCommonData* ftFighterBuildData::getEffectCommonData() {
    return g_ftCommonData.dataCommon->effectCommonData;
}

ftEffectScreenData* ftFighterBuildData::getEffectScreenData() {
    return g_ftCommonData.dataCommon->effectScreenData;
}

soGroundConditionChecker* ftFighterBuildData::getGroundConditionChecker() {
    return &g_ftGroundConditionCheckerImpl;
}

ftJostleData* ftFighterBuildData::getJostleData() {
    return g_ftCommonData.dataCommon->jostleData;
}

ftPreCheckAnimCmdData* ftFighterBuildData::getPreCheckAnimCmdData() {
    return g_ftCommonDataAccesser.getData(m_kind)->preCheckAnimCmdData;
}

float ftFighterBuildData::getModelScale() {
    return g_ftCommonDataAccesser.getParam(m_kind)->modelScale;
}

s32 ftFighterBuildData::getHeapSlotNo() {
    return g_ftManager->getSlotNo(m_entryId);
}

ftSoundIdExchangerImpl* ftFighterBuildData::getSoundIdExchanger() {
    if (m_kind == Fighter_Kirby)
        return &g_ftKirbySoundIdExchangerImpl;
    return &g_ftSoundIdExchangerImpl;
}

float ftFighterBuildData::getSlopeAngleLimit() {
    return g_ftCommonDataAccesser.getParam(m_kind)->slopeAngleLimit;
}

bool ftGroundConditionCheckerImpl::isConditionNoCliffStop(soModuleAccesser* moduleAccesser) {
    soKineticEnergy* energy = moduleAccesser->getKineticModule().getEnergy(4);
    if (energy->isEnable() == true) {
        float f31 = soValueAccesser::getConstantFloat(moduleAccesser, 3297, 0);
        if (energy->getSpeed().lengthSq() > (f31 *= f31))
            return true;
    }
    if (moduleAccesser->getAreaModule().getEnviromentElementChecker()
                                        ->getOnMovementGroundArea() == true)
        return true;
    return false;
}

ftGroundConditionCheckerImpl::~ftGroundConditionCheckerImpl() { }
