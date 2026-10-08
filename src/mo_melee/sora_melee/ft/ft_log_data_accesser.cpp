#pragma force_active on

#include <ft/ft_log_data_accesser.h>

ftLogDataAccesser::ftLogDataAccesser() {
    for (u32 i = 0; i < 22; i++)
        m_floatTable[i] = nullptr;
    for (u32 i = 0; i < 75; i++)
        m_intTable[i] = nullptr;
    for (u32 i = 0; i < 20; i++)
        m_flagTable[i] = nullptr;
}

ftLogDataAccesser::~ftLogDataAccesser() { }

// Binds every table slot to its section of the log data. HYPOTHESIS: the offsets are the layout of ftLogData.
void ftLogDataAccesser::setup(ftLogData* logData) {
    m_floatTable[0] = (float*)((u8*)logData + 0x0);
    m_count[0] = 1;
    m_floatTable[1] = (float*)((u8*)logData + 0x4);
    m_count[1] = 1;
    m_floatTable[2] = (float*)((u8*)logData + 0xC);
    m_count[2] = 1;
    m_floatTable[3] = (float*)((u8*)logData + 0x10);
    m_count[3] = 1;
    m_floatTable[4] = (float*)((u8*)logData + 0x14);
    m_count[4] = 1;
    m_floatTable[5] = (float*)((u8*)logData + 0x18);
    m_count[5] = 7;
    m_floatTable[6] = (float*)((u8*)logData + 0x3C);
    m_count[6] = 1;
    m_floatTable[7] = (float*)((u8*)logData + 0x40);
    m_count[7] = 1;
    m_floatTable[8] = (float*)((u8*)logData + 0x44);
    m_count[8] = 1;
    m_floatTable[9] = (float*)((u8*)logData + 0x7C);
    m_count[9] = 1;
    m_floatTable[10] = (float*)((u8*)logData + 0x80);
    m_count[10] = 1;
    m_floatTable[11] = (float*)((u8*)logData + 0x98);
    m_count[11] = 1;
    m_floatTable[12] = (float*)((u8*)logData + 0x13C);
    m_count[12] = 1;
    m_floatTable[13] = (float*)((u8*)logData + 0x140);
    m_count[13] = 1;
    m_floatTable[14] = (float*)((u8*)logData + 0x144);
    m_count[14] = 1;
    m_floatTable[15] = (float*)((u8*)logData + 0x148);
    m_count[15] = 1;
    m_floatTable[16] = (float*)((u8*)logData + 0x14C);
    m_count[16] = 1;
    m_floatTable[17] = (float*)((u8*)logData + 0x150);
    m_count[17] = 1;
    m_floatTable[18] = (float*)((u8*)logData + 0x154);
    m_count[18] = 1;
    m_floatTable[19] = (float*)((u8*)logData + 0x15C);
    m_count[19] = 1;
    m_floatTable[20] = (float*)((u8*)logData + 0x164);
    m_count[20] = 1;
    m_floatTable[21] = (float*)((u8*)logData + 0x18C);
    m_count[21] = 1;
    m_intTable[0] = (int*)((u8*)logData + 0x8);
    m_count[22] = 1;
    m_intTable[1] = (int*)((u8*)logData + 0x34);
    m_count[23] = 1;
    m_intTable[2] = (int*)((u8*)logData + 0x38);
    m_count[24] = 1;
    m_intTable[3] = (int*)((u8*)logData + 0x48);
    m_count[25] = 1;
    m_intTable[4] = (int*)((u8*)logData + 0x4C);
    m_count[26] = 1;
    m_intTable[5] = (int*)((u8*)logData + 0x50);
    m_count[27] = 1;
    m_intTable[6] = (int*)((u8*)logData + 0x54);
    m_count[28] = 1;
    m_intTable[7] = (int*)((u8*)logData + 0x58);
    m_count[29] = 1;
    m_intTable[8] = (int*)((u8*)logData + 0x5C);
    m_count[30] = 1;
    m_intTable[9] = (int*)((u8*)logData + 0x60);
    m_count[31] = 1;
    m_intTable[10] = (int*)((u8*)logData + 0x64);
    m_count[32] = 1;
    m_intTable[11] = (int*)((u8*)logData + 0x68);
    m_count[33] = 1;
    m_intTable[12] = (int*)((u8*)logData + 0x6C);
    m_count[34] = 1;
    m_intTable[13] = (int*)((u8*)logData + 0x70);
    m_count[35] = 1;
    m_intTable[14] = (int*)((u8*)logData + 0x74);
    m_count[36] = 1;
    m_intTable[15] = (int*)((u8*)logData + 0x78);
    m_count[37] = 1;
    m_intTable[16] = (int*)((u8*)logData + 0x84);
    m_count[38] = 1;
    m_intTable[17] = (int*)((u8*)logData + 0x88);
    m_count[39] = 1;
    m_intTable[18] = (int*)((u8*)logData + 0x8C);
    m_count[40] = 1;
    m_intTable[19] = (int*)((u8*)logData + 0x90);
    m_count[41] = 1;
    m_intTable[20] = (int*)((u8*)logData + 0x94);
    m_count[42] = 1;
    m_intTable[21] = (int*)((u8*)logData + 0x9C);
    m_count[43] = 1;
    m_intTable[22] = (int*)((u8*)logData + 0xA0);
    m_count[44] = 1;
    m_intTable[23] = (int*)((u8*)logData + 0xA4);
    m_count[45] = 1;
    m_intTable[24] = (int*)((u8*)logData + 0xA8);
    m_count[46] = 1;
    m_intTable[25] = (int*)((u8*)logData + 0xAC);
    m_count[47] = 1;
    m_intTable[26] = (int*)((u8*)logData + 0xB0);
    m_count[48] = 1;
    m_intTable[27] = (int*)((u8*)logData + 0xB4);
    m_count[49] = 1;
    m_intTable[28] = (int*)((u8*)logData + 0xB8);
    m_count[50] = 1;
    m_intTable[29] = (int*)((u8*)logData + 0xBC);
    m_count[51] = 1;
    m_intTable[30] = (int*)((u8*)logData + 0xC0);
    m_count[52] = 1;
    m_intTable[31] = (int*)((u8*)logData + 0xC4);
    m_count[53] = 1;
    m_intTable[32] = (int*)((u8*)logData + 0xC8);
    m_count[54] = 1;
    m_intTable[33] = (int*)((u8*)logData + 0xCC);
    m_count[55] = 1;
    m_intTable[34] = (int*)((u8*)logData + 0xD0);
    m_count[56] = 1;
    m_intTable[35] = (int*)((u8*)logData + 0xD4);
    m_count[57] = 1;
    m_intTable[36] = (int*)((u8*)logData + 0xD8);
    m_count[58] = 1;
    m_intTable[37] = (int*)((u8*)logData + 0xDC);
    m_count[59] = 1;
    m_intTable[38] = (int*)((u8*)logData + 0xE0);
    m_count[60] = 1;
    m_intTable[39] = (int*)((u8*)logData + 0xE4);
    m_count[61] = 1;
    m_intTable[40] = (int*)((u8*)logData + 0xE8);
    m_count[62] = 1;
    m_intTable[41] = (int*)((u8*)logData + 0xEC);
    m_count[63] = 1;
    m_intTable[42] = (int*)((u8*)logData + 0xF0);
    m_count[64] = 1;
    m_intTable[43] = (int*)((u8*)logData + 0xF4);
    m_count[65] = 1;
    m_intTable[44] = (int*)((u8*)logData + 0xF8);
    m_count[66] = 1;
    m_intTable[45] = (int*)((u8*)logData + 0xFC);
    m_count[67] = 1;
    m_intTable[46] = (int*)((u8*)logData + 0x100);
    m_count[68] = 1;
    m_intTable[47] = (int*)((u8*)logData + 0x104);
    m_count[69] = 1;
    m_intTable[48] = (int*)((u8*)logData + 0x108);
    m_count[70] = 1;
    m_intTable[49] = (int*)((u8*)logData + 0x10C);
    m_count[71] = 1;
    m_intTable[50] = (int*)((u8*)logData + 0x110);
    m_count[72] = 1;
    m_intTable[51] = (int*)((u8*)logData + 0x114);
    m_count[73] = 1;
    m_intTable[52] = (int*)((u8*)logData + 0x118);
    m_count[74] = 1;
    m_intTable[53] = (int*)((u8*)logData + 0x11C);
    m_count[75] = 1;
    m_intTable[54] = (int*)((u8*)logData + 0x120);
    m_count[76] = 1;
    m_intTable[55] = (int*)((u8*)logData + 0x124);
    m_count[77] = 1;
    m_intTable[56] = (int*)((u8*)logData + 0x128);
    m_count[78] = 1;
    m_intTable[57] = (int*)((u8*)logData + 0x12C);
    m_count[79] = 1;
    m_intTable[58] = (int*)((u8*)logData + 0x130);
    m_count[80] = 1;
    m_intTable[59] = (int*)((u8*)logData + 0x134);
    m_count[81] = 1;
    m_intTable[60] = (int*)((u8*)logData + 0x138);
    m_count[82] = 1;
    m_intTable[61] = (int*)((u8*)logData + 0x158);
    m_count[83] = 1;
    m_intTable[62] = (int*)((u8*)logData + 0x160);
    m_count[84] = 1;
    m_intTable[63] = (int*)((u8*)logData + 0x168);
    m_count[85] = 1;
    m_intTable[64] = (int*)((u8*)logData + 0x16C);
    m_count[86] = 1;
    m_intTable[65] = (int*)((u8*)logData + 0x170);
    m_count[87] = 1;
    m_intTable[66] = (int*)((u8*)logData + 0x174);
    m_count[88] = 1;
    m_intTable[67] = (int*)((u8*)logData + 0x178);
    m_count[89] = 1;
    m_intTable[68] = (int*)((u8*)logData + 0x17C);
    m_count[90] = 1;
    m_intTable[69] = (int*)((u8*)logData + 0x180);
    m_count[91] = 1;
    m_intTable[70] = (int*)((u8*)logData + 0x184);
    m_count[92] = 1;
    m_intTable[71] = (int*)((u8*)logData + 0x188);
    m_count[93] = 1;
    m_intTable[72] = (int*)((u8*)logData + 0x190);
    m_count[94] = 1;
    m_intTable[73] = (int*)((u8*)logData + 0x194);
    m_count[95] = 1;
    m_intTable[74] = (int*)((u8*)logData + 0x198);
    m_count[96] = 1;
    m_flagTable[0] = (bool*)((u8*)logData + 0x19C);
    m_count[97] = 1;
    m_flagTable[1] = (bool*)((u8*)logData + 0x19D);
    m_count[98] = 1;
    m_flagTable[2] = (bool*)((u8*)logData + 0x19E);
    m_count[99] = 1;
    m_flagTable[3] = (bool*)((u8*)logData + 0x19F);
    m_count[100] = 1;
    m_flagTable[4] = (bool*)((u8*)logData + 0x1A0);
    m_count[101] = 1;
    m_flagTable[5] = (bool*)((u8*)logData + 0x1A1);
    m_count[102] = 1;
    m_flagTable[6] = (bool*)((u8*)logData + 0x1A2);
    m_count[103] = 1;
    m_flagTable[7] = (bool*)((u8*)logData + 0x1A3);
    m_count[104] = 1;
    m_flagTable[8] = (bool*)((u8*)logData + 0x1A4);
    m_count[105] = 1;
    m_flagTable[9] = (bool*)((u8*)logData + 0x1A5);
    m_count[106] = 1;
    m_flagTable[10] = (bool*)((u8*)logData + 0x1A6);
    m_count[107] = 1;
    m_flagTable[11] = (bool*)((u8*)logData + 0x1A7);
    m_count[108] = 1;
    m_flagTable[12] = (bool*)((u8*)logData + 0x1A8);
    m_count[109] = 1;
    m_flagTable[13] = (bool*)((u8*)logData + 0x1A9);
    m_count[110] = 1;
    m_flagTable[14] = (bool*)((u8*)logData + 0x1AA);
    m_count[111] = 1;
    m_flagTable[15] = (bool*)((u8*)logData + 0x1AB);
    m_count[112] = 1;
    m_flagTable[16] = (bool*)((u8*)logData + 0x1AC);
    m_count[113] = 1;
    m_flagTable[17] = (bool*)((u8*)logData + 0x1AD);
    m_count[114] = 1;
    m_flagTable[18] = (bool*)((u8*)logData + 0x1AE);
    m_count[115] = 1;
    m_flagTable[19] = (bool*)((u8*)logData + 0x1AF);
    m_count[116] = 1;
}

// Clears the logged values behind every table slot.
void ftLogDataAccesser::reset() {
    for (int i = 0; i < 22; i++)
        for (int j = 0; j < m_count[i]; j++)
            m_floatTable[i][j] = 0.0f;
    for (u32 i = 0; i < 75; i++)
        for (int j = 0; j < m_count[i + 22]; j++)
            m_intTable[i][j] = 0;
    for (s32 i = 0; i < 20; i++)
        for (int j = 0; j < m_count[97 + i]; j++)
            m_flagTable[i][j] = false;
}

float ftLogDataAccesser::getFloat(u32 category, u32 slot) {
    return m_floatTable[category][slot];
}

void ftLogDataAccesser::setFloat(float val, u32 category, u32 slot) {
    m_floatTable[category][slot] = val;
}

void ftLogDataAccesser::addFloat(float val, u32 category, u32 slot) {
    m_floatTable[category][slot] += val;
}

int ftLogDataAccesser::getInt(u32 category, u32 slot) {
    return m_intTable[category][slot];
}

void ftLogDataAccesser::setInt(int val, u32 category, u32 slot) {
    m_intTable[category][slot] = val;
}

void ftLogDataAccesser::addInt(int val, u32 category, u32 slot) {
    m_intTable[category][slot] += val;
}

bool ftLogDataAccesser::isFlag(u32 category, u32 slot) {
    return m_flagTable[category][slot];
}

void ftLogDataAccesser::setFlag(bool val, u32 category, u32 slot) {
    m_flagTable[category][slot] = val;
}

void ftLogDataAccesser::onFlag(u32 category, u32 slot) {
    m_flagTable[category][slot] = true;
}

void ftLogDataAccesser::offFlag(u32 category, u32 slot) {
    m_flagTable[category][slot] = false;
}
