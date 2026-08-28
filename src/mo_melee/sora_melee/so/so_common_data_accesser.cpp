#include <so/so_common_data_accesser.h>
#include <types.h>

soCommonDataAccesser g_soCommonDataAccesser;

void soCommonDataAccesser::setupCommonParam(soCommonParam** p1) {
    for (u32 i = 0; i < 2; i++) {
        u32 j = 0;
        u32 k = 0;
        paramFloats[i].data[j++] = p1[i]->m_0;
        paramFloats[i].data[j++] = p1[i]->m_4;
        paramFloats[i].data[j++] = p1[i]->m_8;
        paramFloats[i].data[j++] = p1[i]->m_C;
        paramFloats[i].data[j++] = p1[i]->m_18;
        paramFloats[i].data[j++] = p1[i]->m_1C;
        paramFloats[i].data[j++] = p1[i]->m_20;
        paramFloats[i].data[j++] = p1[i]->m_24;
        paramFloats[i].data[j++] = p1[i]->m_28;
        paramFloats[i].data[j++] = p1[i]->m_2C;
        paramFloats[i].data[j++] = p1[i]->m_30;
        paramFloats[i].data[j++] = p1[i]->m_34;
        paramFloats[i].data[j++] = p1[i]->m_38;
        paramFloats[i].data[j++] = p1[i]->m_3C;
        paramFloats[i].data[j++] = p1[i]->m_40;
        paramFloats[i].data[j++] = p1[i]->m_48;
        paramFloats[i].data[j++] = p1[i]->m_4C;
        paramFloats[i].data[j++] = p1[i]->m_50;
        paramFloats[i].data[j++] = p1[i]->m_54;
        paramFloats[i].data[j++] = p1[i]->m_5C;
        paramFloats[i].data[j++] = p1[i]->m_60;
        paramFloats[i].data[j++] = p1[i]->m_6C;
        paramFloats[i].data[j++] = p1[i]->m_70;
        paramFloats[i].data[j++] = p1[i]->m_74;
        paramFloats[i].data[j++] = p1[i]->m_78;
        paramFloats[i].data[j++] = p1[i]->m_7C;
        paramFloats[i].data[j++] = p1[i]->m_80;
        paramFloats[i].data[j++] = p1[i]->m_84;
        paramFloats[i].data[j++] = p1[i]->m_88;
        paramFloats[i].data[j++] = p1[i]->m_8C;
        paramFloats[i].data[j++] = p1[i]->m_90;
        paramFloats[i].data[j++] = p1[i]->m_94;
        paramFloats[i].data[j++] = p1[i]->m_98;
        paramFloats[i].data[j++] = p1[i]->m_9C;
        paramFloats[i].data[j++] = p1[i]->m_A0;
        paramFloats[i].data[j++] = p1[i]->m_A4;
        paramFloats[i].data[j++] = p1[i]->m_A8;
        paramFloats[i].data[j++] = p1[i]->m_AC;
        paramFloats[i].data[j++] = p1[i]->m_B0;
        paramFloats[i].data[j++] = p1[i]->m_B4;

        paramInts[i].data[k++] = p1[i]->m_10;
        paramInts[i].data[k++] = p1[i]->m_14;
        paramInts[i].data[k++] = p1[i]->m_44;
        paramInts[i].data[k++] = p1[i]->m_58;
        paramInts[i].data[k++] = p1[i]->m_B8;

        paramIndefinites[i].data[0] = &p1[i]->m_64;
    }
    commonData = p1;
}

float soCommonDataAccesser::getParamCommonFloat(u32 p1, u32 p2) {
    return paramFloats[p1 - 50].data[p2 - 2];
}

s32 soCommonDataAccesser::getParamCommonInt(u32 p1, u32 p2) {
    return paramInts[p1 - 4400].data[p2 - 1];
}

s32* soCommonDataAccesser::getParamCommonIndefinite(u32 p1, u32 p2) {
    return paramIndefinites[p1 - 42000].data[p2 - 1];
}
