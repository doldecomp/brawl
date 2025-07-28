#include <em/rayquaza/wnem_proc_rayquaza.h>
#include <em/wnem/wnem_proc_common.h>
#include <types.h>

void wnemRayquazaProc::LightBallFly(wnemSimple* wn) {
    bool r4 = wn->unk2214;
    wn->unk2214 = false;
    if (r4) {
        wnemCommonProc::Report("call wnemRayquazaProc::LightBallFly  \n");
        wn->setProcFnc_TouchGround(0x1E);
        wn->setProcFnc_LifeZero(0x1F);
    }
    if (wn->unk2215) {
        wn->unk2215 = false;
        wn->executeAnimCmd(1);
    }
}

void wnemRayquazaProc::LightBallLanding(wnemSimple* wn) {
    bool r4 = wn->unk2214;
    wn->unk2214 = false;
    if (r4) {
        wnemCommonProc::Report("call wnemRayquazaProc::LightBallLanding  \n");
        s32* r31 = nullptr;
        if (wn->unk2234) {
            r31 = wn->unk2234;
        }
        wn->executeAnimCmd(1);
        wn->SetDeadMode();
        wn->unk2204 = 0.0f;
        wn->unk2200 = 0.0f;
        wn->unk21FC = 0.0f;
        wn->unk21F8 = 0.0f;
        wn->setProcFnc_LifeZero(0x1F);
        wn->SetLifeLimit(*r31);
        wn->setProcFnc_TouchGround(-1);
    }
}

void wnemRayquazaProc::LightBallDisappear(wnemSimple* wn) {
    s32* r31 = nullptr;
    if (wn->unk2234) {
        r31 = wn->unk2234;
    }
    bool r4 = wn->unk2214;
    wn->unk2214 = false;
    if (r4) {
        wnemCommonProc::Report("call wnemRayquazaProc::LightBallDisappear  \n");
        wn->SetDeadMode();
        wn->executeAnimCmd(0);
        wn->executeAnimCmd(2);
    }
    if (wn->getFrameCounter(1) >= static_cast<u32>(r31[1])) {
        wn->RequestDeactive();
    }
}
