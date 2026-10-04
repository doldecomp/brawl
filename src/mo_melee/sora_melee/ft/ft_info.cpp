#include <ft/ft_info.h>
#include <types.h>

// Per-fighter-kind info tables (55 kinds).
static const char* const s_kindNames[55] = {
    "MARIO",
    "DONKEY",
    "LINK",
    "SAMUS",
    "YOSHI",
    "KIRBY",
    "FOX",
    "PIKACHU",
    "LUIGI",
    "CAPTAIN",
    "NESS",
    "KOOPA",
    "PEACH",
    "ZELDA",
    "SHEIK",
    "POPO",
    "NANA",
    "MARTH",
    "GAMEWATCH",
    "FALCO",
    "GANON",
    "WARIO",
    "METAKNIGHT",
    "PIT",
    "SZEROSUIT",
    "PIKMIN",
    "LUCAS",
    "DIDDY",
    "POKETRAINER",
    "POKELIZARDON",
    "POKEZENIGAME",
    "POKEFUSHIGISOU",
    "DEDEDE",
    "LUCARIO",
    "IKE",
    "ROBOT",
    "PRAMAI",
    "PURIN",
    "MEWTWO",
    "ROY",
    "DR_MARIO",
    "TOONLINK",
    "TOONZELDA",
    "TOONSHEIK",
    "WOLF",
    "DIXIE",
    "SNAKE",
    "SONIC",
    "GKOOPA",
    "WARIOMAN",
    "ZAKOBOY",
    "ZAKOGIRL",
    "ZAKOCHILD",
    "ZAKOBALL",
    "MARIOD"
};

static const u32 s_motionNum[55] = {
    478, 516, 484, 492, 488, 797,
    498, 486, 482, 491, 490, 483,
    481, 480, 486, 498, 498, 501,
    514, 492, 488, 531, 492, 500,
    491, 480, 491, 507, 515, 477,
    484, 477, 535, 491, 500, 487,
    0, 501, 0, 0, 0, 484,
    0, 0, 494, 0, 510, 497,
    484, 531, 463, 463, 463, 463,
    478,
};

static const u32 s_statusNum[55] = {
    281, 309, 284, 301, 293, 448,
    288, 288, 285, 290, 289, 291,
    287, 284, 287, 289, 289, 289,
    313, 285, 290, 305, 290, 289,
    289, 284, 290, 303, 299, 281,
    287, 283, 314, 293, 295, 286,
    0, 288, 0, 0, 0, 284,
    0, 0, 288, 0, 309, 295,
    292, 305, 280, 280, 280, 280,
    281,
};

static const int s_entryArticleId[55] = {
    4, 2, -1, 8, -1, 12, 4, 4,
    2, 0, -1, -1, 0, -1, -1, 5,
    -1, -1, 7, 4, -1, 0, 0, -1,
    -1, 1, 5, 4, -1, -1, -1, -1,
    5, -1, -1, -1, -1, 4, -1, -1,
    -1, -1, -1, -1, 4, -1, 16, -1,
    -1, -1, -1, -1, -1, -1, 4,
};

ftInfo g_ftInfo;

// HYPOTHESIS: the sinit copies a (zero) word that sits right after g_ftInfo in .bss into
// seven slots of this table; modelled as a separate non-const static.
static int s_unkInit;

// HYPOTHESIS: purpose unknown (statically initialised int table indexed by kind).
static int s_unk[55] = {
    63, 63, 80, 48, 78, 61, 68, 48,
    63, 65, 67, 77, 106, 104, 63, 46,
    46, 71, 98, 72, 70, 79, 77, 92,
    67, 46, 65, 71, 48, 58, 47, 55,
    64, 56, 74, 163, s_unkInit, 64, s_unkInit, s_unkInit,
    s_unkInit, 83, s_unkInit, s_unkInit, 73, s_unkInit, 70, 83,
    74, 69, 34, 39, 34, 34, 63,
};

// Per-kind constants (14 ints per kind).
static int s_constInt[55][14] = {
    {1, 3, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1},
    {2, 2, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 2, 0},
    {2, 3, 0, 1, 2, 1, 0, 0, 0, 0, 0, 1, 0, 0},
    {1, 2, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0},
    {2, 2, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1},
    {1, 2, 1, 1, 1, 2, 0, 0, 0, 0, 0, 0, 1, 1},
    {1, 2, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0},
    {0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1},
    {2, 3, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1},
    {1, 3, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0},
    {1, 3, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1},
    {2, 2, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 2, 0},
    {2, 2, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 3, 0},
    {0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 3, 0},
    {1, 2, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 0, 0},
    {2, 2, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1},
    {2, 2, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1},
    {2, 2, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1},
    {1, 2, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0},
    {1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {2, 2, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1},
    {3, 0, 1, 3, 1, 2, 1, 0, 0, 0, 0, 0, 0, 1},
    {2, 3, 1, 1, 1, 2, 1, 0, 0, 0, 0, 0, 0, 0},
    {1, 3, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0},
    {2, 2, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 3, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1},
    {2, 3, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {2, 3, 0, 1, 1, 2, 1, 0, 0, 0, 0, 0, 0, 0},
    {1, 3, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1},
    {1, 2, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1},
    {2, 2, 1, 1, 1, 2, 0, 0, 0, 0, 0, 0, 2, 0},
    {1, 3, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 0, 0},
    {1, 3, 0, 1, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 2, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 2, 0, 1, 1, 2, 0, 0, 0, 0, 0, 0, 1, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {2, 3, 0, 1, 2, 1, 0, 0, 0, 1, 0, 1, 0, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 3, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1},
    {1, 3, 0, 2, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0},
    {1, 3, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0},
    {2, 2, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 2, 0},
    {2, 2, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1},
    {1, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 3, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 2, 1, 1, 1, 2, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 3, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1},
};

bool ftInfo::isInvalidKind(int kind) {
    if (kind > -1 && kind < 0x37) {
        return false;
    }
    return true;
}

int ftInfo::getInvalidKind() {
    return -1;
}

const char* ftInfo::getNamePtr(int kind) {
    return s_kindNames[kind];
}

u32 ftInfo::getMotionNum(int kind) {
    return s_motionNum[kind];
}

u32 ftInfo::getStatusNum(int kind) {
    return s_statusNum[kind];
}

int ftInfo::getEntryArticleID(int kind) {
    return s_entryArticleId[kind];
}

int ftInfo::getConstInt(int kind, int index) {
    return s_constInt[kind][index];
}
