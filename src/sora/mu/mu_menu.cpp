#include <gf/gf_pad_system.h>
#include <types.h>

// Per-character CSS table entry (16 bytes). Stored at lbl_80455458, indexed by CSS selection kind (selchkind).
struct muCharColorInfo {
    u8 gmCharacterKind; // 0xFF if none
    u8 gmCharacterKind2; // alternate (e.g. Pokemon Trainer's sub-characters)
    u8 muCharKind;
    u8 stockchkind;
    u32 unk4;
    const u8* colors; // pairs of {charColorNo, fighterColorFileNo}, terminated by charColorNo == 0xC
    u8 isLarge : 1;
    u8 unkC : 7;
    u8 unkD[3];
};

extern muCharColorInfo lbl_80455458[];

// 3 bytes per MuCharKind (36 entries). Stored at lbl_80407A40.
struct muCharKindInfo {
    u8 gmCharacterKind;
    u8 unk1;
    u8 stockchkind;
};

extern muCharKindInfo lbl_80407A40[];
// {gmCharacterKind, muCharKind} overrides. Stored at lbl_80407BD0.
extern u8 lbl_80407BD0[7][2];
extern const u8 lbl_805A21F0[8];

// Stock icon / voice table entry (16 bytes), 61 entries. Stored at lbl_804556D8.
struct muStockInfo {
    u8 unk0;
    u8 unk1;
    u8 gmCharacterKind;
    u8 gmCharacterKind2;
    u8 unk4;
    u8 unk5[3];
    u32 voice;
    u8 voiceLengthE;
    u8 voiceLengthJ;
    u8 unkE[2];
};

extern muStockInfo lbl_804556D8[];

// Stage table entry (4 bytes), 41 entries. Stored at lbl_80407AAC.
struct muStageInfo {
    u8 srStageKind;
    u8 hideStageKind;
    u8 frameNo;
    u8 msgID;
};

extern muStageInfo lbl_80407AAC[];
extern const u8 lbl_80407B50[];
// {srStageKind, muStageKind} overrides. Stored at lbl_80407BE0.
extern const u8 lbl_80407BE0[10][2];

struct GameGlobal;
extern GameGlobal* g_GameGlobal;
extern "C" u32* fn_8004E580(GameGlobal*); // returns the unlocked-character bitset
extern "C" int fn_8004D9E8(GameGlobal*);
extern "C" int fn_8004D9A8(GameGlobal*, int);
extern "C" int fn_8004DA94(GameGlobal*, int);

// 8 bytes per entry. Stored at lbl_80455AA8.
struct muEntry8 {
    u32 unk0;
    u32 unk4;
};
extern muEntry8 lbl_80455AA8[];
extern const char* lbl_804561E4[];
extern const char* lbl_80456338[];
extern const char* lbl_80456564[];

class muMenu {
public:
    static int exchangeMuCharKindToGmCharacterKind(int, int, int);
    static int exchangeGmCharacterKindToMuCharKind(int, int, int);
    static int exchangeMuCharKindToMuSelchkind(int, int, int);
    static int exchangeMuSelchkindToMuCharKind(int, int, int);
    static int exchangeMuCharKindToMuStockchkind(int, int, int);
    static bool isCharUsable(int, int, int);
    static bool isCharRefered(int, int, int);
    static void setCharRefered(int, int, int);
    static int findCharTeamColorNo(int, int, int);
    static int exchangeMuStageKindToGmHideStageKind(int, int, int);
    static int getInfoMsgID(int, int, int);
    static int exchangeGmCharacterKind2MuStockchkind(int);
    static int exchangeGmCharacterKind2Something(int);
    static int exchangeMuStageKindToSrStageKind(int, int, int);
    static int exchangeSrStageKindToMuStageKind(int, int, int);
    static float getStageFrameNo(int, int, int);
    static int exchangeMuStageKindToMsgID(int, int, int);
    static int exchangeGmCharacterKind2MuSelchkind(int, int, int);
    static int exchangeMuSelchkind2GmCharacterKind(int, int, int);
    static int exchangeMuSelchkind2MuStockchkind(int);
    static int exchangeMuSelchkind2MuStockchkind(int, int, int);
    static int exchangeSelchkind2SelCharVoice(int);
    static int exchangeSelchkind2SelCharNarrationSndID(int, int, int);
    static int exchangeSelCharVoice2SelCharVoiceLengthE(int);
    static int exchangeSelCharVoice2SelCharVoiceLengthJ(int);
    static int getNumCharColor(int charKind, int, int);
    static int getCharColor(int charKind, int costume, int);
    static int getFighterColorFileNo(int charKind, int costume, int);
    static int getCharColorNo(int charKind, int fileNo, int);
    static bool isCharLargeSize(int charKind, int, int);
    static int getCpLevelMessageId(int cpLevel, int, int);
    static const char* exchangeMuStockchkind2MuCharName(int);
    static void startRumbleController(int, int, int);
    static int loadMenuSound();
    static bool isLoadFinishMenuSound();
    static void freeMenuSound(int, int, int);
};

int muMenu::exchangeMuCharKindToGmCharacterKind(int muCharKind, int, int) {
    return lbl_80407A40[muCharKind].gmCharacterKind;
}

int muMenu::exchangeGmCharacterKindToMuCharKind(int gmCharacterKind, int, int) {
    for (int i = 0; i < 7; i++) {
        if (gmCharacterKind == lbl_80407BD0[i][0]) {
            return lbl_80407BD0[i][1];
        }
    }
    int i;
    for (i = 0; i < 36; i++) {
        if (gmCharacterKind == lbl_80407A40[i].gmCharacterKind) {
            break;
        }
    }
    return i;
}

int muMenu::exchangeMuCharKindToMuSelchkind(int muCharKind, int, int) {
    int i;
    for (i = 0; i < 40; i++) {
        if (muCharKind == lbl_80455458[i].muCharKind) {
            break;
        }
    }
    return i;
}

int muMenu::exchangeMuSelchkindToMuCharKind(int selchkind, int, int) {
    return lbl_80455458[selchkind].muCharKind;
}

int muMenu::exchangeMuCharKindToMuStockchkind(int muCharKind, int, int) {
    return lbl_80407A40[muCharKind].stockchkind;
}

bool muMenu::isCharUsable(int muCharKind, int, int) {
    u32* bits = fn_8004E580(g_GameGlobal);
    int unlockIdx = lbl_80407A40[muCharKind].unk1;
    if (unlockIdx != 0xE) {
        int bit = unlockIdx * 3 + 1;
        if (!(bits[bit / 32] & (1 << (bit % 32)))) {
            return false;
        }
    }
    return true;
}

bool muMenu::isCharRefered(int muCharKind, int, int) {
    u32* bits = fn_8004E580(g_GameGlobal);
    int unlockIdx = lbl_80407A40[muCharKind].unk1;
    if (unlockIdx != 0xE) {
        int bit = unlockIdx * 3 + 2;
        if (!(bits[bit / 32] & (1 << (bit % 32)))) {
            return false;
        }
    }
    return true;
}

void muMenu::setCharRefered(int muCharKind, int, int) {
    u32* bits = fn_8004E580(g_GameGlobal);
    int unlockIdx = lbl_80407A40[muCharKind].unk1;
    if (unlockIdx != 0xE) {
        int bit = unlockIdx * 3 + 2;
        bits[bit / 32] |= 1 << (bit % 32);
    }
}

int muMenu::findCharTeamColorNo(int selchkind, int teamColor, int colorNo) {
    u8 want = lbl_805A21F0[teamColor];
    const u8* colors = lbl_80455458[selchkind].colors;
    const u8* c = colors + colorNo * 2;
    for (; colorNo < getNumCharColor(selchkind, 0, 0); colorNo++) {
        if ((int)want == (int)*c) {
            break;
        }
        c += 2;
    }
    return colorNo;
}

int muMenu::exchangeMuStageKindToGmHideStageKind(int muStageKind, int, int) {
    return lbl_80407AAC[muStageKind].hideStageKind;
}

int muMenu::getInfoMsgID(int idx, int, int) {
    return lbl_80407B50[idx];
}

int muMenu::exchangeGmCharacterKind2MuStockchkind(int gmCharacterKind) {
    int i;
    for (i = 0; i < 61; i++) {
        if (gmCharacterKind == lbl_804556D8[i].gmCharacterKind || gmCharacterKind == lbl_804556D8[i].gmCharacterKind2) {
            break;
        }
    }
    if (i == 61) {
        i = 0;
    }
    return i;
}

int muMenu::exchangeGmCharacterKind2Something(int gmCharacterKind) {
    return lbl_804556D8[gmCharacterKind].unk0;
}

int muMenu::exchangeMuStageKindToSrStageKind(int muStageKind, int, int) {
    return lbl_80407AAC[muStageKind].srStageKind;
}

int muMenu::exchangeSrStageKindToMuStageKind(int srStageKind, int, int) {
    for (int i = 0; i < 10; i++) {
        if (srStageKind == lbl_80407BE0[i][0]) {
            return lbl_80407BE0[i][1];
        }
    }
    int i;
    for (i = 0; i < 41; i++) {
        if (srStageKind == lbl_80407AAC[i].srStageKind) {
            break;
        }
    }
    return i;
}

float muMenu::getStageFrameNo(int muStageKind, int, int) {
    return lbl_80407AAC[muStageKind].frameNo;
}

int muMenu::exchangeMuStageKindToMsgID(int muStageKind, int, int) {
    return lbl_80407AAC[muStageKind].msgID;
}

extern "C" int fn_800AF6F0(int idx) {
    return lbl_804556D8[idx].unk4;
}

int muMenu::exchangeGmCharacterKind2MuSelchkind(int gmCharacterKind, int, int) {
    int i;
    for (i = 0; i < 40; i++) {
        if (gmCharacterKind == lbl_80455458[i].gmCharacterKind || gmCharacterKind == lbl_80455458[i].gmCharacterKind2) {
            break;
        }
    }
    return i;
}

int muMenu::exchangeMuSelchkind2GmCharacterKind(int selchkind, int, int) {
    u32 kind = lbl_80455458[selchkind].gmCharacterKind;
    if (kind == 0xFF) {
        kind = 0x3E;
    }
    return kind;
}

int muMenu::exchangeMuSelchkind2MuStockchkind(int selchkind) {
    return lbl_80455458[selchkind].stockchkind;
}

int muMenu::exchangeMuSelchkind2MuStockchkind(int selchkind, int, int) {
    return lbl_80455458[selchkind].unk4;
}

int muMenu::exchangeSelchkind2SelCharVoice(int selchkind) {
    return lbl_804556D8[selchkind].voice;
}

int muMenu::exchangeSelchkind2SelCharNarrationSndID(int selchkind, int, int) {
    muStockInfo& stock = lbl_804556D8[lbl_80455458[selchkind].stockchkind];
    return stock.voice;
}

int muMenu::exchangeSelCharVoice2SelCharVoiceLengthE(int voice) {
    return lbl_804556D8[voice].voiceLengthE;
}

int muMenu::exchangeSelCharVoice2SelCharVoiceLengthJ(int voice) {
    return lbl_804556D8[voice].voiceLengthJ;
}

int muMenu::getNumCharColor(int charKind, int, int) {
    const u8* c = lbl_80455458[charKind].colors;
    int n = 0;
    while (*c != 0xC) {
        c += 2;
        n++;
    }
    return n;
}

extern "C" int fn_800AF904(int idx) {
    return lbl_804556D8[idx].unk1;
}

int muMenu::getCharColor(int charKind, int costume, int) {
    return lbl_80455458[charKind].colors[costume * 2];
}

int muMenu::getFighterColorFileNo(int charKind, int costume, int) {
    const u8* c = lbl_80455458[charKind].colors + costume * 2;
    return c[1];
}

int muMenu::getCharColorNo(int charKind, int colorNo, int) {
    const muCharColorInfo* info = &lbl_80455458[charKind];
    int n = getNumCharColor(charKind, 0, 0);
    for (int i = 0; i < n; i++) {
        if (colorNo == info->colors[i * 2]) {
            return i;
        }
    }
    return -1;
}

bool muMenu::isCharLargeSize(int charKind, int, int) {
    return lbl_80455458[charKind].isLarge;
}

int muMenu::getCpLevelMessageId(int cpLevel, int, int) {
    return cpLevel == 9 ? 0x18 : cpLevel + 0xF;
}

extern "C" u32 fn_800AFA04(int idx) {
    return lbl_80455AA8[idx].unk4;
}

extern "C" u32 fn_800AFA1C(int idx) {
    return lbl_80455AA8[idx].unk0;
}

const char* muMenu::exchangeMuStockchkind2MuCharName(int stockchkind) {
    if (fn_8004D9E8(g_GameGlobal)) {
        return lbl_804561E4[stockchkind];
    }
    return lbl_80456564[stockchkind];
}

extern "C" const char* fn_800AFA8C(int idx) {
    if (fn_8004D9E8(g_GameGlobal)) {
        const char* name = lbl_80456338[idx];
        if (name == 0) {
            name = lbl_80456564[idx];
        }
        return name;
    }
    return lbl_80456564[idx];
}

void muMenu::startRumbleController(int controller, int strength, int setting) {
    int enabled;
    if (setting >= 0) {
        enabled = fn_8004D9A8(g_GameGlobal, setting);
    } else {
        enabled = fn_8004DA94(g_GameGlobal, controller);
    }
    if (enabled) {
        gfPadSystem* pad = g_gfPadSystem;
        if (strength > 0) {
            pad->startMotor(controller, strength);
        } else {
            pad->startMotor(controller);
        }
    }
}

int muMenu::loadMenuSound() {
    return -1;
}

bool muMenu::isLoadFinishMenuSound() {
    return true;
}

void muMenu::freeMenuSound(int, int, int) {
}
