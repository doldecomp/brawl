#include <nw4r/g3d.h>

#include <revolution/BASE.h>
#include <revolution/GX.h>

namespace nw4r {
namespace g3d {

void ResTev::GXSetTevSwapModeTable(GXTevSwapSel swap, GXTevColorChan r,
                                   GXTevColorChan g, GXTevColorChan b,
                                   GXTevColorChan a) {
    u8* pCmd = ref().dl.dl.common.dl.swapModeTable[swap];
    u32 cmd;

    // clang-format off
    detail::ResWriteSSMask(&pCmd[GX_BP_CMD_SZ * 0],
                           GX_BP_TEVKSEL_SWAP_RB_MASK | GX_BP_TEVKSEL_SWAP_GA_MASK);

    cmd = 0;
    cmd |= r << GX_BP_TEVKSEL_SWAP_RB_SHIFT;
    cmd |= g << GX_BP_TEVKSEL_SWAP_GA_SHIFT;
    cmd |= (swap * 2 + GX_BP_REG_TEVKSEL0) << GX_BP_OPCODE_SHIFT;

    detail::ResWriteBPCmd(&pCmd[GX_BP_CMD_SZ * 1], cmd,
        ~(GX_BP_TEVKSEL_KASEL_ODD_MASK | GX_BP_TEVKSEL_KCSEL_ODD_MASK |
          GX_BP_TEVKSEL_KASEL_EVEN_MASK | GX_BP_TEVKSEL_KCSEL_EVEN_MASK));

    detail::ResWriteSSMask(&pCmd[GX_BP_CMD_SZ * 2],
                           GX_BP_TEVKSEL_SWAP_RB_MASK | GX_BP_TEVKSEL_SWAP_GA_MASK);

    cmd = 0;
    cmd |= b << GX_BP_TEVKSEL_SWAP_RB_SHIFT;
    cmd |= a << GX_BP_TEVKSEL_SWAP_GA_SHIFT;
    cmd |= (swap * 2 + GX_BP_REG_TEVKSEL1) << GX_BP_OPCODE_SHIFT;

    detail::ResWriteBPCmd(&pCmd[GX_BP_CMD_SZ * 3], cmd,
        ~(GX_BP_TEVKSEL_KASEL_ODD_MASK | GX_BP_TEVKSEL_KCSEL_ODD_MASK |
          GX_BP_TEVKSEL_KASEL_EVEN_MASK | GX_BP_TEVKSEL_KCSEL_EVEN_MASK));
    // clang-format on
}

void ResTev::GXSetTevSwapMode(GXTevStageID stage, GXTevSwapSel ras,
                              GXTevSwapSel tex) {
    u8* pCmd = ref().dl.dl.var[stage / TEV_STAGES_PER_DL].dl.alphaCalcAndSwap[stage % TEV_STAGES_PER_DL];

    detail::ResWriteBPCmd(pCmd, (ras | tex << 2) | (stage * 2 + 0xC1) << 24,
                          0xFF00000F);
}

void ResTev::GXSetTevAlphaIn(GXTevStageID stage, GXTevAlphaArg a,
                             GXTevAlphaArg b, GXTevAlphaArg c,
                             GXTevAlphaArg d) {
    u8* pCmd = ref().dl.dl.var[stage / TEV_STAGES_PER_DL].dl.alphaCalcAndSwap[stage % TEV_STAGES_PER_DL];

    detail::ResWriteBPCmd(pCmd,
                          (d << 4) | (c << 7) | (b << 10) | (a << 13) |
                              (stage * 2 + 0xC1) << 24,
                          0xFF00FFF0);
}

void ResTev::GXSetTevAlphaOp(GXTevStageID stage, GXTevOp op, GXTevBias bias,
                         GXTevScale scale, GXBool clamp, GXTevRegID out) {
    u8* pCmd = ref().dl.dl.var[stage / TEV_STAGES_PER_DL].dl.alphaCalcAndSwap[stage % TEV_STAGES_PER_DL];
    u32 cmd;

    if (op <= GX_TEV_SUB) {
        cmd = (out << 22) | (scale << 20) | (clamp << 19) | bias << 16 |
              ((op & 1) << 18) | (stage * 2 + 0xC1) << 24;
    } else {
        cmd = (out << 22) | ((op & 6) << 19) | ((op & 1) << 18) |
              (clamp << 19) | (3 << 16) | (stage * 2 + 0xC1) << 24;
    }

    detail::ResWriteBPCmd(pCmd, cmd, 0xFFFF0000);
}

bool ResTev::GXGetTevKColorSel(GXTevStageID stage,
                               GXTevKColorSel* pSel) const {
    const u8* pCmd = ref().dl.dl.var[stage / TEV_STAGES_PER_DL].dl.tevKonstantSel;
    u32 cmd;

    if (pCmd[0] == 0) {
        return false;
    }

    detail::ResReadBPCmd(&pCmd[GX_BP_CMD_SZ * 1], &cmd);

    if (stage & 1) {
        *pSel = static_cast<GXTevKColorSel>(cmd >> 14 & 0x1F);
    } else {
        *pSel = static_cast<GXTevKColorSel>(cmd >> 4 & 0x1F);
    }

    return true;
}

void ResTev::GXSetTevKColorSel(GXTevStageID stage, GXTevKColorSel sel) {
    int idx = stage / TEV_STAGES_PER_DL;
    u8* pCmd = ref().dl.dl.var[idx].dl.tevKonstantSel;
    u32 shift = (stage & 1) ? 14 : 4;
    u32 mask = 0x1F << shift;

    detail::ResWriteSSMask(&pCmd[GX_BP_CMD_SZ * 0], mask);
    detail::ResWriteBPCmd(&pCmd[GX_BP_CMD_SZ * 1],
                          (idx + 0xF6) << 24 | sel << shift,
                          mask | 0xFF000000);
}

void ResTev::GXSetTevKAlphaSel(GXTevStageID stage, GXTevKAlphaSel sel) {
    int idx = stage / TEV_STAGES_PER_DL;
    u8* pCmd = ref().dl.dl.var[idx].dl.tevKonstantSel;
    u32 shift = (stage & 1) ? 19 : 9;
    u32 mask = 0x1F << shift;

    detail::ResWriteSSMask(&pCmd[GX_BP_CMD_SZ * 0], mask);
    detail::ResWriteBPCmd(&pCmd[GX_BP_CMD_SZ * 1],
                          (idx + 0xF6) << 24 | sel << shift,
                          mask | 0xFF000000);
}

bool ResTev::GXGetTevOrder(GXTevStageID stage, GXTexCoordID* pCoord,
                           GXTexMapID* pMap, GXChannelID* pChannel) const {
    // Convert RAS channel ID to GX channel ID
    static const GXChannelID r2c[GX_RAS_MAX_CHANNEL] = {
        GX_COLOR0A0,   GX_COLOR1A1,   GX_COLOR_NULL,  GX_COLOR_NULL,
        GX_COLOR_NULL, GX_ALPHA_BUMP, GX_ALPHA_BUMPN, GX_COLOR_ZERO};

    const u8* pCmd = ref().dl.dl.var[stage / TEV_STAGES_PER_DL].dl.tevOrder;

    if (pCmd[0] == 0) {
        return false;
    }

    u32 cmd;
    detail::ResReadBPCmd(pCmd, &cmd);

    bool enabled;
    GXTexCoordID coord;
    GXTexMapID map;
    GXChannelID channel;

    if (stage & 1) {
        channel = r2c[cmd >> GX_BP_RAS1_TREF_COLORCHAN_ODD_SHIFT &
                      GX_BP_RAS1_TREF_COLORCHAN_ODD_LMASK];

        coord = static_cast<GXTexCoordID>(
            cmd >> GX_BP_RAS1_TREF_TEXCOORD_ODD_SHIFT &
            GX_BP_RAS1_TREF_TEXCOORD_ODD_LMASK);

        enabled = cmd >> GX_BP_RAS1_TREF_ENABLE_TEX_ODD_SHIFT &
                  GX_BP_RAS1_TREF_ENABLE_TEX_ODD_LMASK;

        map = static_cast<GXTexMapID>(cmd >> GX_BP_RAS1_TREF_TEXMAP_ODD_SHIFT &
                                      GX_BP_RAS1_TREF_TEXMAP_ODD_LMASK);
    } else {
        channel = r2c[cmd >> GX_BP_RAS1_TREF_COLORCHAN_EVEN_SHIFT &
                      GX_BP_RAS1_TREF_COLORCHAN_EVEN_LMASK];

        coord = static_cast<GXTexCoordID>(
            cmd >> GX_BP_RAS1_TREF_TEXCOORD_EVEN_SHIFT &
            GX_BP_RAS1_TREF_TEXCOORD_EVEN_LMASK);

        enabled = cmd >> GX_BP_RAS1_TREF_ENABLE_TEX_EVEN_SHIFT &
                  GX_BP_RAS1_TREF_ENABLE_TEX_EVEN_LMASK;

        map = static_cast<GXTexMapID>(cmd >> GX_BP_RAS1_TREF_TEXMAP_EVEN_SHIFT &
                                      GX_BP_RAS1_TREF_TEXMAP_EVEN_LMASK);
    }

    if (pCoord != NULL) {
        *pCoord = coord;
    }

    if (pChannel != NULL) {
        *pChannel = channel;
    }

    if (!enabled) {
        map = GX_TEXMAP_NULL;
    }

    if (pMap) {
        *pMap = map;
    }

    return true;
}

void ResTev::GXSetTevOrder(GXTevStageID stage, GXTexCoordID coord,
                           GXTexMapID map, GXChannelID channel) {
    // Convert GX channel ID to RAS channel ID
    static u8 c2r[16] = {0, 1, 0, 1, 0, 1, 7, 5, 6, 0, 0, 0, 0, 0, 0, 7};

    GXTexCoordID oldCoord;
    GXTexMapID oldMap;

    if (GXGetTevOrder(stage, &oldCoord, &oldMap, NULL) &&
        oldCoord != GX_TEXCOORD_NULL && oldMap != GX_TEXMAP_NULL) {
        ref().texCoordToTexMapID[oldCoord] = GX_TEXMAP_NULL;
    }

    if (coord != GX_TEXCOORD_NULL) {
        ref().texCoordToTexMapID[coord] = map;
    }

    u8* pCmd = ref().dl.dl.var[stage / TEV_STAGES_PER_DL].dl.tevOrder;
    u32 shift = -(stage & 1) & 12;

    u32 enable = 0;
    if (map != GX_TEXMAP_NULL && (map & 0x100) == 0) {
        enable = 1;
    }

    detail::ResWriteBPCmd(
        pCmd,
        ((c2r[channel & 0xF] << 7 | (map & 7) | (coord & 7) << 3 |
          enable << 6)
         << shift) |
            (stage / 2 + 0x28) << 24,
        0x3FF << shift | 0xFF000000);
}

bool ResTev::GXGetTevColorIn(GXTevStageID stage, GXTevColorArg* pA,
                             GXTevColorArg* pB, GXTevColorArg* pC,
                             GXTevColorArg* pD) const {
    const u8* pCmd = ref().dl.dl.var[stage / TEV_STAGES_PER_DL].dl.tevColorCalc[stage % TEV_STAGES_PER_DL];
    u32 cmd;

    if (pCmd[0] == 0) {
        return false;
    }

    detail::ResReadBPCmd(pCmd, &cmd);

    if (pA != NULL) {
        *pA = static_cast<GXTevColorArg>(cmd >> 12 & 0xF);
    }

    if (pB != NULL) {
        *pB = static_cast<GXTevColorArg>(cmd >> 8 & 0xF);
    }

    if (pC != NULL) {
        *pC = static_cast<GXTevColorArg>(cmd >> 4 & 0xF);
    }

    if (pD != NULL) {
        *pD = static_cast<GXTevColorArg>(cmd & 0xF);
    }

    return true;
}

void ResTev::GXSetTevColorIn(GXTevStageID stage, GXTevColorArg a,
                             GXTevColorArg b, GXTevColorArg c,
                             GXTevColorArg d) {
    u8* pCmd = ref()
                   .dl.dl.var[stage / TEV_STAGES_PER_DL]
                   .dl.tevColorCalc[stage % TEV_STAGES_PER_DL];

    // clang-format off
    detail::ResWriteBPCmd(pCmd,
        (d << GX_BP_TEVCOLORCOMBINER_D_SHIFT) |
        (c << GX_BP_TEVCOLORCOMBINER_C_SHIFT) |
        (b << GX_BP_TEVCOLORCOMBINER_B_SHIFT) |
        (a << GX_BP_TEVCOLORCOMBINER_A_SHIFT) |
        ((GX_BP_REG_TEVCOLORCOMBINER0 + stage * 2)
            << GX_BP_OPCODE_SHIFT),

        ~(GX_BP_TEVCOLORCOMBINER_DEST_MASK |
          GX_BP_TEVCOLORCOMBINER_SCALE_OR_COMPARE_MODE_MASK |
          GX_BP_TEVCOLORCOMBINER_CLAMP_MASK |
          GX_BP_TEVCOLORCOMBINER_OP_OR_COMPARISON_MASK |
          GX_BP_TEVCOLORCOMBINER_BIAS_MASK));
    // clang-format on
}

void ResTev::GXSetTevColorOp(GXTevStageID stage, GXTevOp op, GXTevBias bias,
                         GXTevScale scale, GXBool clamp, GXTevRegID out) {
    u8* pCmd = ref().dl.dl.var[stage / TEV_STAGES_PER_DL].dl.tevColorCalc[stage % TEV_STAGES_PER_DL];
    u32 cmd;

    if (op <= GX_TEV_SUB) {
        cmd = (out << 22) | (scale << 20) | (clamp << 19) | bias << 16 |
              ((op & 1) << 18) | (stage * 2 + 0xC0) << 24;
    } else {
        cmd = (out << 22) | ((op & 6) << 19) | ((op & 1) << 18) |
              (clamp << 19) | (3 << 16) | (stage * 2 + 0xC0) << 24;
    }

    detail::ResWriteBPCmd(pCmd, cmd, 0xFFFF0000);
}

void ResTev::SetNumTevStages(u8 num) {
    if (num != 0 && num <= GX_MAX_TEVSTAGE) {
        ResTevData& r = ref();

        if (num < r.nStages) {
            for (u32 i = num; i < r.nStages; i++) {
                GXSetTevOrder(static_cast<GXTevStageID>(i), GX_TEXCOORD_NULL,
                              GX_TEXMAP_NULL, GX_COLOR_NULL);
            }

            for (u32 i = (num + 1) / 2; i < (r.nStages + 1) >> 1; i++) {
                ResTevVariableDL* pVar = &r.dl.dl.var[i];

                detail::ZeroMemory16ByteBlocks(pVar, sizeof(ResTevVariableDL));
                DC::StoreRangeNoSync(pVar, sizeof(ResTevVariableDL));
            }
        }

        r.nStages = num;
    }
}

void ResTev::CallDisplayList(bool sync) const {
    // Variable DL holds data for two GX tev stages
    static const u32 dlsize[GX_MAX_TEVSTAGE] = {
        ROUND_UP(sizeof(ResTevCommonDL) + 1 * sizeof(ResTevVariableDL), 32),
        ROUND_UP(sizeof(ResTevCommonDL) + 1 * sizeof(ResTevVariableDL), 32),
        ROUND_UP(sizeof(ResTevCommonDL) + 2 * sizeof(ResTevVariableDL), 32),
        ROUND_UP(sizeof(ResTevCommonDL) + 2 * sizeof(ResTevVariableDL), 32),
        ROUND_UP(sizeof(ResTevCommonDL) + 3 * sizeof(ResTevVariableDL), 32),
        ROUND_UP(sizeof(ResTevCommonDL) + 3 * sizeof(ResTevVariableDL), 32),
        ROUND_UP(sizeof(ResTevCommonDL) + 4 * sizeof(ResTevVariableDL), 32),
        ROUND_UP(sizeof(ResTevCommonDL) + 4 * sizeof(ResTevVariableDL), 32),
        ROUND_UP(sizeof(ResTevCommonDL) + 5 * sizeof(ResTevVariableDL), 32),
        ROUND_UP(sizeof(ResTevCommonDL) + 5 * sizeof(ResTevVariableDL), 32),
        ROUND_UP(sizeof(ResTevCommonDL) + 6 * sizeof(ResTevVariableDL), 32),
        ROUND_UP(sizeof(ResTevCommonDL) + 6 * sizeof(ResTevVariableDL), 32),
        ROUND_UP(sizeof(ResTevCommonDL) + 7 * sizeof(ResTevVariableDL), 32),
        ROUND_UP(sizeof(ResTevCommonDL) + 7 * sizeof(ResTevVariableDL), 32),
        ROUND_UP(sizeof(ResTevCommonDL) + 8 * sizeof(ResTevVariableDL), 32),
        ROUND_UP(sizeof(ResTevCommonDL) + 8 * sizeof(ResTevVariableDL), 32)};

    if (sync) {
        PPCSync();
    }

    GXCallDisplayList(const_cast<ResTevDL*>(&ref().dl),
                      dlsize[GetNumTevStages() - 1]);
}

ResTev ResTev::CopyTo(void* pDst) {
    const ResTevData* pSrc = &ref();
    detail::Copy32ByteBlocks(pDst, pSrc, sizeof(ResTevData));

    ResTev tev(pDst);
    tev.ref().toResMdlData -= reinterpret_cast<std::uintptr_t>(pDst) -
                              reinterpret_cast<std::uintptr_t>(pSrc);

    tev.DCStore(false);
    return tev;
}

void ResTev::DCStore(bool sync) {
    void* pBase = &ref();
    u32 size = ref().size;

    if (sync) {
        DC::StoreRange(pBase, size);
    } else {
        DC::StoreRangeNoSync(pBase, size);
    }
}

} // namespace g3d
} // namespace nw4r
