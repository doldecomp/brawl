#include <cm/cm_camera_controller.h>
#include <gf/gf_archive.h>
#include <gm/gm_lib.h>
#include <memory.h>
#include <mt/mt_prng.h>
#include <nw4r/g3d/g3d_resfile.h>
#include <snd/snd_id.h>
#include <snd/snd_system.h>
#include <st_config/gr_config.h>
#include <st/stage.h>
#include <st/st_class_info.h>
#include <st/st_melee.h>
#include <types.h>

#include <st_config/st_config.h>

stClassInfoImpl<Stages::Config, stConfig> stConfig::bss_loc_14;

stConfig::stConfig() : stMelee("stConfig", Stages::Config) {
//	initStageData();
}

stConfig* stConfig::create() {
    return new (Heaps::StageInstance) stConfig;
}

stConfig::~stConfig() {
    releaseArchive();
}

bool stConfig::loading() {
    return true;
}

void stConfig::createObj() {
    testStageParamInit(m_fileData, 10);
    testStageDataInit(m_fileData, 20,1);
    grConfig *ground = grConfig::create(1,"", "grConfigMainBg");
    if (ground) {
        addGround(ground);
        ground->startup(this->m_fileData,0,0);
        createCollision(m_fileData, 2, 0);
        initCameraParam();
        nw4r::g3d::ResFile posData(m_fileData->getData(Data_Type_Model, 0x64, 0xFFFE));
        if (posData.ptr()) {
            nw4r::g3d::ResFile copyPosData = posData;
            createStagePositions(&copyPosData);
        } else {
            createStagePositions();
        }
        createWind2ndOnly();
        loadStageAttrParam(m_fileData, 0x1E);
        registScnAnim(static_cast<nw4r::g3d::ResFileData*>(m_fileData->getData(Data_Type_Scene, 0, 0xFFFE)), 0);
    }
}

