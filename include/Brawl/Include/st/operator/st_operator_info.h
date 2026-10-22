#pragma once

#include <StaticAssert.h>
#include <st/operator/st_operator.h>
#include <st/loader/st_loader_player.h>
#include <gm/gm_lib.h>
#include <types.h>

class stOperatorInfo : public stOperator {
public:
    stLoaderPlayer* m_loaderPlayers[MAX_PLAYERS];
    s8 m_playersCursorStatus[MAX_PLAYERS];
    s8 m_playersNameCursorStatus[MAX_PLAYERS];
    char _0x74[0x42];
    s8 m_playersLoupeStatus[MAX_PLAYERS];
    char _0x7B[0x60];

    virtual void processBegin();
    virtual void processEnd();
    virtual ~stOperatorInfo();
    virtual void startOperator();
    virtual void stopOperatorRequest();
    virtual bool isEnableOperation();
    virtual u32 getEndType();
    virtual u32 getErrorLevel();
    virtual bool isError();
    virtual void setPlayerCursorClear(u8 index);
    virtual void setPlayerCursorStatus(u8 index, s8 status);
    virtual void setPlayerNameCursorStatus(u8 index, s8 status);
    virtual void setPlayerLoupeStatus(u8 index, s8 status);
    virtual void updatePlayerCursor(bool);

};
static_assert(sizeof(stOperatorInfo) == 0x11c, "Class is wrong size!");
