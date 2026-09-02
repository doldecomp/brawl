#pragma once

#include <StaticAssert.h>
#include <gr/gr_yakumono.h>
#include <types.h>
#include <ms/ms_message.h>

class grPictchat : public grYakumono {
protected:
    u8 unk110;
    float unk114;
public:
    grPictchat(const char* taskName);
    virtual ~grPictchat();
};

class grPictchatBg : public grYakumono {
protected:
    u8 unk150;
    float unk154;
    void *unk15C;
    void *msgData;
    u32 pictIDWork;
    grCollisionJoint *unk168;
public:
	bool isMessageInit;
	Message* message;
	u32 selectedPlayerNo;
	
	//static grPictchatBg();
    grPictchatBg(const char* taskName);
    static grPictchatBg* create(int mdlIndex, const char *tgtNodeName, const char *taskName);
    virtual void setMsgData(void *param1);
    virtual void setPictIDWork(char param1);
    virtual void update(float param1);
    virtual void updateJoint(float param1);
    virtual void updateMessage(float param1);
    virtual ~grPictchatBg();
};
//static_assert(sizeof(grPictchat) == 0x158, "Class is the wrong size!");
