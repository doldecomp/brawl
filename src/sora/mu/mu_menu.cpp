#include <types.h>

// Per-character CSS table entry (16 bytes). Stored at lbl_80455458, indexed by CSS char kind.
struct muCharColorInfo {
    u8 unk0[8];
    const u8* colors; // pairs of {charColorNo, fighterColorFileNo}, terminated by charColorNo == 0xC
    u8 isLarge : 1;
    u8 unkC : 7;
    u8 unkD[3];
};

extern muCharColorInfo lbl_80455458[];

struct muStockInfo {
    u8 unk0;
    u8 unk1;
    u8 unk2[14];
};

extern muStockInfo lbl_804556D8[];

class muMenu {
public:
    static int getNumCharColor(int charKind, int, int);
    static int getCharColor(int charKind, int costume, int);
    static int getFighterColorFileNo(int charKind, int costume, int);
    static int getCharColorNo(int charKind, int fileNo, int);
    static bool isCharLargeSize(int charKind, int, int);
    static int getCpLevelMessageId(int cpLevel, int, int);
};

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
