#pragma once

#include <gr/gr_yakumono.h>
#include <types.h>

class grVillage : public grYakumono {
  protected:
    u8 m_state;
    float m_stateTimer;
    u8* m_sceneWork;
    unsigned char m_sceneBit;
    char* m_stateWork;
    int* m_guestPositionsWork;
  public:
    grVillage(const char* taskName);
	static grVillage* create(int mdlIndex, const char *tgtNodeName, const char *taskName);
    virtual void update(float deltaFrame);
    virtual void updateVisible(float deltaFrame);
    virtual void setSceneWork(char* sceneWork);
    virtual void setSceneBit(char sceneBit);
    virtual void setStateWork(char* stateWork);
    virtual void setPosGuestWork(int* guestPositions);
    virtual bool isSceneBit();
    virtual ~grVillage();
};