#include <so/effect/so_effect_module_impl.h>
#include <so/so_module_accesser.h>
#include <em/arman/wnem_proc_arman.h>
#include <em/wnem/wnem_proc_common.h>
#include <types.h>

void wnemArmanProc::ArmEnter(wnemSimple* wn, soModuleAccesser* acc) {
    s32* r31;
    bool r4 = wn->unk2214;
    wn->unk2214 = false;
    if (r4) {
        wnemCommonProc::Report("call wnemArmanProc::ArmEnter  \n");
        wn->setProcFnc_HpZero(0xE);
        wn->changeMotion(0, false);
        wn->executeAnimCmd(0);
        wn->executeAnimCmd(1);
        r31 = wn->unk2234;
        if (r31) {
            soEffectModuleImpl& ref = dynamic_cast<soEffectModuleImpl&>(
                acc->getEffectModule());
            ref.unk50 = r31[1];
        }
    }
}

void wnemArmanProc::ArmExit(wnemSimple* wn, soModuleAccesser* acc) {
    bool r4 = wn->unk2214;
    wn->unk2214 = false;
    if (r4) {
        wnemCommonProc::Report("wnemArmanProc::ArmExit : OnEnter \n");
        wn->changeMotion(1, false);
        wn->setProcFnc_HpZero(0xE);
    } else if (acc->getMotionModule().isEnd()) {
        wn->RequestDeactive();
    }
}

void wnemArmanProc::ArmIdol(wnemSimple* wn) {
    bool r4 = wn->unk2214;
    wn->unk2214 = false;
    if (r4) {
        wnemCommonProc::Report("call wnemArmanProc::ArmIdol  \n");
        wn->setProcFnc_HpZero(0xE);
    }
}

void wnemArmanProc::ArmDead(wnemSimple* wn, soModuleAccesser* acc) {
    s32* r30 = nullptr;
    if (wn->unk2234) {
        r30 = wn->unk2234;
    }
    bool r4 = wn->unk2214;
    wn->unk2214 = false;
    if (r4) {
        wnemCommonProc::Report("call wnemArmanProc::ArmDead  \n");
        wn->unk21B8 = false;
        wn->unk21BB = false;
        UnkLinkEvent unk(0x13FF, 3);
        acc->getLinkModule().sendEventParents(3, unk);
    }
    if (wn->getFrameCounter(1) >= r30[0]) {
        wn->RequestDeactive();
    }
}
