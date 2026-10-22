#pragma once

#include <StaticAssert.h>
#include <ft/ft_entry.h>
#include <so/so_common_data_accesser.h>
#include <types.h>

struct soAnimCmdDisguiseList {
    s32 unk0;
    void* unk4;
};

struct ftData {
    ftMotionData* motionData;
    ftVisibilityData* visibilityData;
    u8 unk8[0xC];
    ftStatusData* statusData;
    u8 unk18[0x14];
    ftPreCheckAnimCmdData* preCheckAnimCmdData;
    void* unk30;
    void* unk34;
    void* unk38;
    void* unk3C;
    u8 unk40[0x10];
    soAnimCmdDisguiseList* unk50;
    soAnimCmdDisguiseList* unk54;
};

struct ftParam {
    u8 unk0[0xB4];
    float modelScale;
    u8 unkB8[0x1E0];
    float slopeAngleLimit;
};

struct ftParamEtc {

};

struct ftKindData {
    ftData* data;
    ftParam** params;
    ftParamEtc* ParamEtc;
};

struct ftDataCommon {
    soCommonParam* soCommonParams[2];
    ftCommonParam* ftCommonParams[2];
    void* commonActionEntryScripts;
    void* commonActionExitScripts;
    void* flashOverlayScripts;
    ftShakeData* shakeData;
    u8 unk20[0x8];
    ftJostleData* jostleData;
    u8 unk2C[0x1C];
    GXColor subColors;
    ftEffectCommonData* effectCommonData;
    ftEffectScreenData* effectScreenData;
    ftIkData* ikData;
};

struct ftCommonData {
    ftDataCommon* dataCommon;
    ftCommonParam** commonParams;
    ftCommonParamFloat commonFloatParams[2];
    ftCommonParamInt commonIntParams[2];
    ftCommonParamIndefinite commonIndefiniteParams[2];
};

class ftCommonDataAccesser {
public:
    ftData* getData(ftKind kind) const;
    ftParam* getParam(ftKind kind) const;
};

extern ftCommonData g_ftCommonData;
extern ftCommonDataAccesser g_ftCommonDataAccesser;
