#pragma once

#include <memory.h>
#include <types.h>
#include <gf/gf_archive.h>
#include <gm/gm_lib.h>
#include <gr/gr_madein.h>
#include <gr/gr_tengan_event.h>
#include <mt/mt_vector.h>
#include <snd/snd_id.h>
#include <st/se_util.h>
#include <st/stage.h>
#include <st/st_class_info.h>
#include <st/st_melee.h>

ST_CLASS_INFO

class stPictchat : public stMelee {
	

public:
	int unk1d8;
	float unk1dC;
	//	int unk1e1;
	char unk1e0;
	char unk1e1;
	char unk1e2;
	char unk1e3;
	char unk1e4;
	//int unk1e5;
	//int unk1e6;
	//int unk1e7;
	//int unk1e8;
	//int unk1e9;
	//int unk1ea;
	//int unk1eb;
	//int unk1ec;
	//int unk1ed;
	//int unk1ee;
	//int unk1ef;
	//int unk1f0;
	//int unk1f1;
	//int unk1f2;
	//int unk1f3;
	//int unk1f4;
	//int unk1f5;
	//int unk1f6;
	//int unk1f7;
	//int unk1f8;
	//int unk1f9;
	//int unk1fa;
	//int unk1fb;
	//int unk1fc;
	//int unk1fd;
	//int unk1fe;
	//int unk1ff;
	char pictIDList[27];
	char unk200;
	char unk201;
	char unk202;
	char unk203;
	char unk204;
	char unk205;
	char unk206;
	stDataMultiContainer *unk208;
	stDataMultiContainer *unk20C;
	stDataMultiContainer *unk210;
	stDataMultiContainer *unk214;
	stDataMultiContainer *unk218;
	stDataMultiContainer *unk21C;
	stDataMultiContainer *unk220;
	stDataMultiContainer *unk224;
	stDataMultiContainer *unk228;
	stDataMultiContainer *unk22C;
	stDataMultiContainer *unk230;
	stDataMultiContainer *unk234;
	stDataMultiContainer *unk238;
	stDataMultiContainer *unk23C;
	stDataMultiContainer *unk240;
	stDataMultiContainer *unk244;
	stDataMultiContainer *unk248;
	stDataMultiContainer *unk24C;
	stDataMultiContainer *unk250;
	stDataMultiContainer *unk254;
	stDataMultiContainer *unk258;
	stDataMultiContainer *unk25C;
	stDataMultiContainer *unk260;
	stDataMultiContainer *unk264;
	stDataMultiContainer *unk268;
	stDataMultiContainer *unk26C;
	stDataMultiContainer *unk270;
	
	char unk430;
	stTrigger *windTrigger;
	grGimmickWindData *windAreaData;
    stPictchat();
    //virtual ~stPictChat();
    //virtual void createObj();
    //virtual bool loading();
    //virtual bool startAppear();
    //virtual void setAppearKind(u8 kind);
    //virtual void endAppear();
    //virtual void forceStopAppear();
    //virtual bool isAppear();
    //virtual s32 isStartAppearTimming();
    //virtual void update(float deltaFrame);
    //virtual bool checkChangeScene();
    //virtual void resetChangeScene();
    //virtual void setChangeSceneNumber(s32 n);

    //virtual int getFinalTechniqColor() { return 0x14000496; }
    //virtual IfSmashAppearTask* getAppearTask() { return m_smash_taunt_task; }
    //virtual bool isBamperVector() { return true; }
    //virtual int getPokeTrainerDrawLayer() { return 1; }

    static stPictchat* create();
    virtual bool loading();
    virtual void createObj();
    virtual void createObjBg(int index);
    virtual void createObjSideBar(int index);
    virtual void createObjSideBarLamp(int index);
    virtual void createObjPict(int index);
    virtual void createObjAttack(int index);
    virtual void createObjHashigo();
    virtual void createObjHashigo(int index);
    virtual void createObjSpring();
    virtual void createObjWind();
    virtual void createObjSpring(int index);
    virtual void update();
    virtual void updatePict();
    virtual void initStageDataTbl();
    virtual void initPictIDList();
    virtual bool isBamperVector() { return true; }
    static stClassInfoImpl<Stages::PictChat, stPictchat> bss_loc_14;
};
