#pragma once

#include <StaticAssert.h>
#include <mu/menu.h>
#include <mu/mu_menu_controller.h>
#include <mu/mu_object.h>
#include <mu/selchar/mu_selchar.h>
#include <mu/selchar/mu_select_character_list.h>
#include <mu/selchar/mu_select_character_name_entry.h>
#include <nw4r/g3d/g3d_resfile.h>
#include <mu/selchar/mu_selchar_hand.h>
#include <gf/gf_pad_status.h>
#include <gm/gm_lib.h>
#include <types.h>

class muSelCharCBCalcWorld;

class muSelCharPlayerArea {
protected:
public:
    u32 _0;
    muMenuController m_menuController;
    char _0xAC[0x4];
    MuObject* m_muBackplate;
    MuObject* m_muPlayerNum;
    MuObject* m_muFranchiseIcon;
    MuObject* m_muFrag;
    MuObject* m_muCharPic;
    MuObject* m_muUnk;
    MuObject* m_muCharName;
    MuObject* m_muTagBtn;
    MuObject* m_muNameplate;
    MuObject* m_muHandicap;
    MuObject* m_muComputerLvl;
    char _0xDC[0x74];
    void* m_objProcTask;
    muSelCharCBCalcWorld m_calcWorldCBs[MAX_PLAYERS];
    muSelCharHand* m_selCharHand;
    muSelCharCoin* m_selCharCoin;
    int m_areaIdx;
    int m_playerKind;
    MuSelchkind m_charKind;
    int m_charColorNo;
    int m_teamColor;
    u8 m_teamSet;
    char _0x1C5[3];
    int m_nameId;
    char _0x1CC[0x10];
    int m_controllerNo;
    gfPadType::PadType m_controllerKind;
    char _0x1E4[0x4];
    int m_selectedZelda;
    int m_selectedSamus;
    int m_selectedPoke;
    muSelCharTask* m_selCharTask;
    char _0x1F8[0x4];
    MuSelctChrList m_chrList;
    char _0x35C[0x14];
    MuSelctChrNameEntry m_nameEntry;
    char _0x404[0x34];
    nw4r::g3d::ResFileData* m_charPicData;
    nw4r::g3d::ResFile m_charPicRes;
    char _0x440[0x8];

    void setCharPic(int charKind, int playerKind, int curCostume, bool isTeamBattle, int teamColor, int unk);
    nw4r::g3d::ResFile* getCharPicTexResFile(int charKind);
    bool isTeamBattle();
    u8 exchangeCharKindDetail(MuSelchkind selCharKind);
    void dispMarkKind(MuSelchkind charKind);
    void setCharKind(MuSelchkind charKind);
};
static_assert(sizeof(muSelCharPlayerArea) == 0x448, "Wrong size for class!");
