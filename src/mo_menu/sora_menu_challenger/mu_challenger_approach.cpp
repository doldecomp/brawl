#include "gf/gf_pad_system.h"
#include "gm/gm_global.h"
#include <cstdio>
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
    m_unk4C = NULL;
    m_unk50 = NULL;

    m_animState = 0;
    m_frameCount = 0;
}

muChallengerApproachTask::~muChallengerApproachTask() {}

void muChallengerApproachTask::processDefault() {

    gfPadStatus status;
    g_gfPadSystem->getSysPadStatus(g_GameGlobal->m_modeMelee->m_playersInitData[0].m_controllerNo - 1, &status);

    // NOTE: No idea why, but...
    //  ... cases 0, 11, and 12 are intentionally just breaks
    //  ... cases 1, 4, 5, and 7 are intentionally just incrementing-sets
    switch (m_animState) {
    case 0:
        break;
    case 1:
        m_animState = 2;
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        m_animState = 5;
        break;
    case 5:
        m_animState = 6;
        break;
    case 6:
        break;
    case 7:
        m_animState = 8;
        break;
    case 8:
        break;
    case 9:
        break;
    case 10:
        break;
    case 11:
        break;
    case 12:
        break;
    }

    m_frameCount++;
}

void muChallengerApproachTask::initialize(int param) {
    m_unk54 = param;
    unk2C_b1 = false;
    m_unk58 = 0;
}

void muChallengerApproachTask::release() {
    m_unk48->exit();
    m_unk48 = NULL;

    m_unk40.Release();
    m_unk44.Release();

    delete m_unk4C;
    m_unk4C = NULL;

    delete m_unk50;
    m_unk50 = NULL;
}

void muChallengerApproachTask::createData(gfArchive* archive) {
    // TODO: implement
}
