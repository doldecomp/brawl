#include "gf/gf_archive.h"
#include "gf/gf_pad_system.h"
#include "gm/gm_global.h"
#include "mu/mu_menuroot.h"
#include "snd/snd_system.h"
#include <cstdio>
#include <cstring>
#include <sora_menu_challenger/mu_challenger_approach.h>

muChallengerApproachTask* muChallengerApproachTask::create() {
    return new (Heaps::MenuInstance) muChallengerApproachTask();
}

muChallengerApproachTask::muChallengerApproachTask() : gfTask("ChallengerApproach", Category_Menu, 0xF, 8, true) {
    memset(m_names, 0, sizeof(m_names));

    sprintf(m_names[0], "MenChallenger0001_TopN");
    sprintf(m_names[1], "MenChallenger0002_TopN");
    sprintf(m_names[2], "MenChallenger0003_TopN");
    sprintf(m_names[3], "MenChallenger0004_TopN");
    sprintf(m_names[4], "MenChallenger0005_TopN");
    sprintf(m_names[5], "MenChallenger0006_TopN");
    sprintf(m_names[6], "MenChallenger0007_TopN");
    sprintf(m_names[7], "MenChallenger0008_TopN");
    sprintf(m_names[8], "MenChallenger0009_TopN");
    sprintf(m_names[9], "MenChallenger0010_TopN");
    sprintf(m_names[10], "MenChallenger0011_TopN");
    sprintf(m_names[11], "MenChallenger0012_TopN");
    sprintf(m_names[12], "MenChallenger0013_TopN");
    sprintf(m_names[13], "MenChallenger0014_TopN");

    m_unk48 = NULL;
    m_backgroundAnim = NULL;
    m_challengerAnim = NULL;

    m_animState = 0;
    m_frameCount = 0;
}

muChallengerApproachTask::~muChallengerApproachTask() {}

void muChallengerApproachTask::processDefault() {


    gfPadStatus status;
    g_gfPadSystem->getSysPadStatus((u8)g_GameGlobal->m_modeMelee->m_playersInitData[0].m_controllerNo - 1, &status);

    // NOTE: No idea why, but...
    //  ... cases 0, 11, and 12 are intentionally just breaks
    //  ... cases 1, 4, 5, and 7 are intentionally just incrementing-sets
    switch (m_animState) {
    case 0:
        break;

    case 1:
        m_animState = 2;
        break;

    case 2: {
        char animName[64];
        memset(animName, 0, sizeof(animName));
        strcat(animName, m_names[m_challengerIndex]);
        strcat(animName, "__0");

        m_backgroundAnim->changeNodeAnimNIf("MenChallenger0000_TopN__0");
        m_backgroundAnim->changeVisAnimNIf("MenChallenger0000_TopN__0");
        m_backgroundAnim->changeClrAnimN("MenChallenger0000_TopN__0");

        m_challengerAnim->changeNodeAnimNIf(animName);
        m_challengerAnim->changeVisAnimNIf(animName);
        m_challengerAnim->changeClrAnimN(animName);

        m_soundHandle = g_sndSystem->playSE(snd_se_Dispay_challenger_siren, -1, 0, 0, -1);
        m_animState = 3;
        break; 
    }

    case 3: {
        bool done;
        if (!m_backgroundAnim->isNodeAnimFinished()) done = false;
        else if (!m_backgroundAnim->isVisAnimFinished()) done = false;
        else if (!m_backgroundAnim->isClrAnimFinished()) done = false;
        else if (!m_challengerAnim->isNodeAnimFinished()) done = false;
        else if (!m_challengerAnim->isVisAnimFinished()) done = false;
        else if (!m_challengerAnim->isClrAnimFinished()) done = false;
        else done = true;

        if (done == true) {
            m_animState = 4;
        }
        break;
    }

    case 4:
        m_animState = 5;
        break;

    case 5:
        m_animState = 6;
        break;

    case 6: {
        u32 pressed = status.m_buttonsPressedThisFrame.bits;
        bool advance;
        if (pressed & gfPadButtons::A) advance = true;
        else if (pressed & gfPadButtons::B) advance = true;
        else if (pressed & gfPadButtons::Start) advance = true;
        else advance = pressed & 0x100000;   // unknown button

        if (advance == true) {
            g_sndSystem->playSE(SND_SE_SYSTEM_FIXED_L, -1, 0, 0, -1);
            m_animState = 7;
        }
        break;
    }

    case 7:
        m_animState = 8;
        break;

    case 8: {
        char animName[64];
        memset(animName, 0, sizeof(animName));
        strcat(animName, m_names[m_challengerIndex]);
        strcat(animName, "__1");

        m_backgroundAnim->changeNodeAnimNIf("MenChallenger0000_TopN__1");
        m_backgroundAnim->changeVisAnimNIf("MenChallenger0000_TopN__1");
        m_backgroundAnim->changeClrAnimN("MenChallenger0000_TopN__1");

        m_challengerAnim->changeNodeAnimNIf(animName);
        m_challengerAnim->changeVisAnimNIf(animName);
        m_challengerAnim->changeClrAnimN(animName);

        m_animState = 9;
        break;
    }

    case 9: {
        bool done;
        if (!m_backgroundAnim->isNodeAnimFinished()) done = false;
        else if (!m_backgroundAnim->isVisAnimFinished()) done = false;
        else if (!m_backgroundAnim->isClrAnimFinished()) done = false;
        else if (!m_challengerAnim->isNodeAnimFinished()) done = false;
        else if (!m_challengerAnim->isVisAnimFinished()) done = false;
        else if (!m_challengerAnim->isClrAnimFinished()) done = false;
        else done = true;

        if (done == true) {
            m_animState = 10;
        }
        break;
    }

    case 10:
        g_sndSystem->stopSE((s32)m_soundHandle, 0);
        m_animState = 11;
        break;

    case 11:
        break;

    case 12:
        break;
    }

    m_frameCount++;
}

void muChallengerApproachTask::initialize(int param) {
    m_challengerIndex = param;
    unk2C_b1 = false;
    m_soundHandle = 0;
}

void muChallengerApproachTask::release() {
    m_unk48->exit();
    m_unk48 = NULL;

    m_unk40.Release();
    m_unk44.Release();

    delete m_backgroundAnim;
    m_backgroundAnim = NULL;

    delete m_challengerAnim;
    m_challengerAnim = NULL;
}

void muChallengerApproachTask::createData(gfArchive* archive) {
    m_unk40 = archive->getData(Data_Type_Model, 0, 0xFFFE);
    m_unk44 = archive->getData(Data_Type_Model, 1, 0xFFFE);

    nw4r::g3d::ResFile::Init(&m_unk40);
    nw4r::g3d::ResFile::Init(&m_unk44);

    m_unk48 = MenuRoot::create("ChallengerTask", 0x10, "/menu/defaultcamera/CharacterSelect.brres");

    m_backgroundAnim = MuObject::create(&m_unk40, "MenChallenger0000_TopN", 1, 0, Heaps::MenuInstance);
    m_challengerAnim = MuObject::create(&m_unk44, m_names[m_challengerIndex], 1, 0, Heaps::MenuInstance);

    m_unk48->scene->Insert(m_unk48->scene->sceneItemsCount, m_backgroundAnim->m_scnMdl);
    m_unk48->scene->Insert(m_unk48->scene->sceneItemsCount, m_challengerAnim->m_scnMdl);
}
