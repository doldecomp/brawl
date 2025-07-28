#include <em/taboo/wnem_proc_taboo.h>
#include <em/wnem/wnem_proc_common.h>
#include <types.h>

void wnemTabooProc::BodySplitBulletFly(wnemSimple* wn) {
    bool r4 = wn->unk2214;
    wn->unk2214 = false;
    if (r4) {
        wnemCommonProc::Report("call wnemTabooProc::BodySplitBulletFly  \n");
        wn->setProcFnc_TouchGround(0x21);
        wn->setProcFnc_LifeZero(0x21);
        wn->setProcFnc_HitShell(0x21);
    }
    if (wn->unk2218) {
        wn->changeProcFnc(0x21, 1);
    }
}

void wnemTabooProc::BodySplitBulletExplosion(wnemSimple* wn) {
    s32* r31 = nullptr;
    if (wn->unk2234) {
        r31 = wn->unk2234;
    }
    bool r4 = wn->unk2214;
    wn->unk2214 = false;
    if (r4) {
        wnemCommonProc::Report("call wnemTabooProc::BodySplitBulletExplosion  \n");
        wn->SetDeadMode();
        if (r31[1]) {
            wn->executeAnimCmd(r31[1], 4, 1);
        }
        wn->unk2204 = 0.0f;
        wn->unk2200 = 0.0f;
        wn->unk21FC = 0.0f;
        wn->unk21F8 = 0.0f;
    }
    if (wn->getFrameCounter(1) >= r31[0]) {
        wn->RequestDeactive();
    }
}

void wnemTabooProc::CometBulletFly(wnemSimple* wn) {
    bool r4 = wn->unk2214;
    wn->unk2214 = false;
    if (r4) {
        wnemCommonProc::Report("call wnemTabooProc::CometBulletFly  \n");
        s32* r31 = nullptr;
        if (wn->unk2234) {
            r31 = wn->unk2234;
        }
        wn->SetLifeLimit(r31[2]);
        wn->setProcFnc_LifeZero(0x23);
    }
}

void wnemTabooProc::CometBulletExplosion(wnemSimple* wn) {
    s32* r31 = nullptr;
    if (wn->unk2234) {
        r31 = wn->unk2234;
    }
    bool r4 = wn->unk2214;
    wn->unk2214 = false;
    if (r4) {
        wnemCommonProc::Report("call wnemTabooProc::CometBulletExplosion  \n");
        wn->SetDeadMode();
        if (r31[1]) {
            wn->executeAnimCmd(r31[4], 4, 1);
        }
        wn->unk2204 = 0.0f;
        wn->unk2200 = 0.0f;
        wn->unk21FC = 0.0f;
        wn->unk21F8 = 0.0f;
    }
    if (wn->getFrameCounter(1) >= r31[3]) {
        wn->RequestDeactive();
    }
}
