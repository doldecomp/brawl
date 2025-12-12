//#include <StaticAssert.h>
#include <gf/gf_archive.h>
#include <gm/gm_lib.h>
#include <gr/gr_madein.h>
#include <it/it_manager.h>
#include <memory.h>
#include <types.h>
#include <ec/ec_mgr.h>
#include <gf/gf_archive.h>
#include <gf/gf_3d_scene.h>
#include <gm/gm_lib.h>
//#include <gr/gr_madein.h>
#include <mt/mt_matrix.h>
#include <mt/mt_vector.h>
#include <nw4r/g3d/g3d_resfile.h>
#include <snd/snd_system.h>
#include <st/stage.h>
#include <st/st_data_container.h>
#include <st/st_melee.h>
#include <mt/mt_prng.h>

#include <st_pictchat/gr_pictchat.h>
#include <st_pictchat/st_pictchat.h>

char conversion = 1;

stClassInfoImpl<Stages::PictChat, stPictchat> stPictchat::bss_loc_14;

stPictchat* stPictchat::create() {
	return new (Heaps::StageInstance) stPictchat();
}

stPictchat::stPictchat() : stMelee("stPictchat", Stages::PictoChat)  {
	unk1d8 = 0;
	unk1e0 = 1;
	unk1e1 = 0;
	unk1e2 = 0;
	unk1e3 = 0;
	unk1e4 = 0;
	pictIDList[27];
	unk200 = 0xff;
	unk201 = 5;
	unk202 = 5;
	unk203 = 5;
	unk204 = 5;
	unk205 = 5;
	unk206 = 5;
	windTrigger = 0x0;
	windAreaData = 0x0;
	unk430 = 0xffffffff;
}

bool stPictchat::loading() {
	return true;
}

void stPictchat::createObj() {
    testStageParamInit(m_fileData, 6);
    testStageDataInit(m_fileData, 4, 0x14);
	this->initStageDataTbl();
	this->createObjWind();
	this->createObjBg(0);
	this->createObjPict(1);
	this->createObjPict(2);
	this->createObjPict(3);
	this->createObjPict(4);
	this->createObjPict(5);
	this->createObjPict(6);
	this->createObjPict(7);
	this->createObjPict(8);
	this->createObjPict(9);
	this->createObjPict(10);
	this->createObjPict(11);
	this->createObjPict(12);
	this->createObjPict(13);
	this->createObjPict(14);
	this->createObjPict(15);
	this->createObjPict(16);
	this->createObjPict(17);
	this->createObjPict(18);
	this->createObjPict(19);
	this->createObjPict(20);
	this->createObjPict(21);
	this->createObjPict(22);
	this->createObjPict(23);
	this->createObjPict(24);
	this->createObjPict(25);
	this->createObjPict(26);
	this->createObjPict(27);
	this->createObjPict(28);
	this->createObjPict(29);
    createCollision(m_fileData, 2, 0x0);
	this->createObjSideBar(30);
	this->createObjSideBarLamp(31);
	this->createObjHashigo();
	this->createObjSpring();
	this->createObjAttack(39);
	this->createObjAttack(40);
	this->createObjAttack(41);
	this->createObjAttack(42);
	this->createObjAttack(43);
	this->createObjAttack(44);
    initCameraParam();
    nw4r::g3d::ResFile posData(m_fileData->getData(Data_Type_Model, 0x64, 0xfffe));
    if (posData.ptr()) {
        nw4r::g3d::ResFile copyPosData = posData;
        createStagePositions(&copyPosData);
    } else {
        // if no stgPos model in pac, use defaults
        createStagePositions();
    }
    createWind2ndOnly();
    //m_wind2ndTrigger->setAreaSleep(1);
    //for (size_t i = 0; i < getGroundNum(); i++) {
    //    static_cast<grMadein*>(getGround(i))->initializeEntity();
    //}
    //static_cast<grMadein*>(getGround(3))->startEntityAutoLoop();
    loadStageAttrParam(m_fileData, 8);
    nw4r::g3d::ResFileData* scn = (nw4r::g3d::ResFileData*) m_secondaryFileData->getData(Data_Type_Scene, 0, 0xFFFE);
    registScnAnim(scn, 0);
    initPosPokeTrainer(1, 0);
    createObjPokeTrainer(m_fileData, 0x1f5, "PokeTrainer00", m_pokeTrainerPos, 0);
}

void stPictchat::createObjBg(int index) {
	void *pVar1;
	grPictchatBg *bg;
	switch (index) {
		case 0:
			bg = grPictchatBg::create(1,"StgPictchat00Ground","grPictchatMainBg");
			break;
		default:
			bg = 0;
			break;
	}
	if (bg != 0) {
		this->addGround(bg);
		bg->startup(m_fileData,0,0);
		bg->setStageData(m_stageData);
		
		pVar1 = this->m_fileData->getData(Data_Type_Misc,300,0xfffe);
		bg->setMsgData(pVar1);
		bg->setPictIDWork(this->unk1e1);
	}
}

//void Ground::setStageData(void* stageData) {
//	this->m_stageData = stageData;
//}

void grPictchatBg::setMsgData(void *param1) {
	this->msgData = param1;
}

void grPictchatBg::setPictIDWork(char param1) {
	this->pictIDWork = param1;
}

void stPictchat::createObjSideBar(int index) {
	return;
}

void stPictchat::createObjSideBarLamp(int index) {
	return;
}

void stPictchat::createObjPict(int index) {
	void *pict;
	char *pcVar7;
	pcVar7 = "stPictchat";
	switch(index) {
	default:
		pict = 0x0;
		break;
	case 1:
		pict = 0x0;
		pcVar7[0] = '1';
		break;
	}
	
	if (pict) {
		
	}
	return;
}

void stPictchat::createObjAttack(int index) {
	return;
}

void stPictchat::createObjHashigo() {
	return;
}

void stPictchat::createObjHashigo(int index) {
	return;
}

void stPictchat::createObjSpring() {
	return;
}

void stPictchat::createObjWind() {
	grGimmickWindData *pgVar1;
	stTrigger *windTrigger;
	
	pgVar1 = new grGimmickWindData();
	this->windAreaData = pgVar1;
	
	if (pgVar1) {
		memset(pgVar1,0,0x40);
		pgVar1 = this->windAreaData;
		pgVar1->m_pos.m_x = 0.0;
		pgVar1->m_pos.m_y = 36.0;
		pgVar1->m_pos.m_z = 0.0;
		this->windAreaData->m_speed = 0.5;
		this->windAreaData->m_vector = 200.0;
		pgVar1 = this->windAreaData;
		pgVar1->m_areaData.m_offsetPos.m_x = 0.0;
		pgVar1->m_areaData.m_offsetPos.m_y = 0.0;
		pgVar1->m_areaData.m_range.m_x = 200.0;
		pgVar1->m_areaData.m_range.m_y = 80.0;
		windTrigger = g_stTriggerMng->createTrigger(Gimmick::Area_Wind,-1);
		this->windTrigger = windTrigger;
		windTrigger->setWindTrigger(this->windAreaData);
		//m_wind2ndData->m_areaData = this->windAreaData->m_areaData;
		
		memset(m_wind2ndData,0,0x4c);
		m_wind2ndData->m_pos.m_x = 0.0;
		m_wind2ndData->m_pos.m_y = 36.0;
		m_wind2ndData->m_pos.m_z = 0.0;
		m_wind2ndData->m_speed = 0.5;
		m_wind2ndData->m_vector = 200.0;
		m_wind2ndData->m_60 = 195.0;
		m_wind2ndData->m_64 = 20.0;
		m_wind2ndData->m_68 = 1.5;
		m_wind2ndData->m_72 = 80;
		//pgVar1 = this->windAreaData;
		m_wind2ndData->m_areaData.m_offsetPos.m_x = 0.0;
		m_wind2ndData->m_areaData.m_offsetPos.m_y = 0.0;
		m_wind2ndData->m_areaData.m_range.m_x = 200.0;
		m_wind2ndData->m_areaData.m_range.m_y = 80.0;
		
		this->windTrigger->setWindParam(m_wind2ndData,1);
		this->windTrigger->setAreaSleep(1);
	}
	return;
}

void stPictchat::createObjSpring(int index) {
	return;
}
//void stPictchat::fn_73_28B8() { //initPict
	
//}
//void stPictchat::fn_73_28B8() { //initPict
	
//}
//void stPictchat::fn_73_28B8() { //initPict
	
//}
//void stPictchat::fn_73_28B8() { //initPict
	
//}
//void stPictchat::fn_73_28B8() { //initPict
	
//}
void stPictchat::update() {
	this->updatePict();
}

void stPictchat::updatePict() {
	void *uVar2;
	char bVar4;
	void *puVar5 = this->m_stageData;
	if (puVar5 != 0) {
		bVar4 = this->unk1d8;
		if (bVar4 = 2) {
			if (this->unk1dC == 0.0 || this->unk1e1 == 29) {
				this->unk1e1 = 29;
				this->unk1d8 = 3;
			}
		} else if (bVar4 < 2) {
			if (bVar4 == 0) {
				if (this->unk1e0 == 29) {
					g_sndSystem->playSE(snd_se_stage_Crayon_season01,0,0,0,-1);
					this->unk1e0 = 0;
				}
			}
			this->unk1d8 = 1;
		} else if (this->unk1dC == 0.0) {
			if (26 < this->unk200) {
				this->initPictIDList();
				this->unk200 = 0;
			}
			this->unk1e1 = this->pictIDList[this->unk200];
			bVar4 = this->unk1e4 + 1;
			this->unk1e2 = this->unk1e1;
			this->unk1e4 = bVar4;
			if (23 < bVar4) {
				this->unk1e4 = 23;
			}
			switch (this->unk1e1) {
				case 1:
					g_sndSystem->playSE(snd_se_stage_Crayon_season01,0,0,0,-1);
					break;
				case 2:
					g_sndSystem->playSE(snd_se_stage_Crayon_season02,0,0,0,-1);
					break;
				case 3:
					g_sndSystem->playSE(snd_se_stage_Crayon_season01,0,0,0,-1);
					break;
				case 4:
					g_sndSystem->playSE(snd_se_stage_Crayon_season01,0,0,0,-1);
					break;
				case 5:
					g_sndSystem->playSE(snd_se_stage_Crayon_season01,0,0,0,-1);
					break;
				case 6:
					g_sndSystem->playSE(snd_se_stage_Crayon_season01,0,0,0,-1);
					break;
				case 7:
					g_sndSystem->playSE(snd_se_stage_Crayon_season01,0,0,0,-1);
					break;
				case 8:
					g_sndSystem->playSE(snd_se_stage_Crayon_season01,0,0,0,-1);
					break;
				case 9:
					g_sndSystem->playSE(snd_se_stage_Crayon_season01,0,0,0,-1);
					break;
				case 10:
					g_sndSystem->playSE(snd_se_stage_Crayon_season01,0,0,0,-1);
					break;
				case 11:
					g_sndSystem->playSE(snd_se_stage_Crayon_season01,0,0,0,-1);
					break;
				case 12:
					g_sndSystem->playSE(snd_se_stage_Crayon_season01,0,0,0,-1);
					break;
				case 13:
					g_sndSystem->playSE(snd_se_stage_Crayon_season01,0,0,0,-1);
					break;
				case 14:
					g_sndSystem->playSE(snd_se_stage_Crayon_season01,0,0,0,-1);
					break;
				case 15:
					g_sndSystem->playSE(snd_se_stage_Crayon_season01,0,0,0,-1);
					break;
				case 16:
					g_sndSystem->playSE(snd_se_stage_Crayon_season01,0,0,0,-1);
					break;
				case 17:
					g_sndSystem->playSE(snd_se_stage_Crayon_season01,0,0,0,-1);
					break;
				case 18:
					g_sndSystem->playSE(snd_se_stage_Crayon_season01,0,0,0,-1);
					break;
				case 19:
					g_sndSystem->playSE(snd_se_stage_Crayon_season01,0,0,0,-1);
					break;
				case 20:
					g_sndSystem->playSE(snd_se_stage_Crayon_season01,0,0,0,-1);
					break;
				case 21:
					g_sndSystem->playSE(snd_se_stage_Crayon_season01,0,0,0,-1);
					break;
				case 22:
					g_sndSystem->playSE(snd_se_stage_Crayon_season01,0,0,0,-1);
					break;
				case 23:
					g_sndSystem->playSE(snd_se_stage_Crayon_season01,0,0,0,-1);
					break;
				case 24:
					g_sndSystem->playSE(snd_se_stage_Crayon_season01,0,0,0,-1);
					break;
				case 25:
					g_sndSystem->playSE(snd_se_stage_Crayon_season01,0,0,0,-1);
					break;
				case 26:
					g_sndSystem->playSE(snd_se_stage_Crayon_season01,0,0,0,-1);
					break;
				case 27:
					g_sndSystem->playSE(snd_se_stage_Crayon_season01,0,0,0,-1);
					break;
			}
			this->unk1d8 = 2;
		}
	} else if (bVar4 < 4 && this->unk1e1 == 29) {
		this->unk1d8 = 0;
	}
}

void stPictchat::initStageDataTbl() {
	gfArchive *data;
	void *pgVar1;
	stDataMultiContainer *psVar2;
	data = this->m_fileData;
	if (data != 0) {
		pgVar1 = data->getData(Data_Type_Misc,0xa,0xfffe);
		if (pgVar1 != 0) {
			psVar2 = stDataMultiContainer::create(pgVar1,Heaps::StageInstance);
			this->unk208 = psVar2;
		}
		pgVar1 = this->m_fileData->getData(Data_Type_Misc,0x14,0xfffe);
		if (pgVar1 != 0) {
			psVar2 = stDataMultiContainer::create(pgVar1,Heaps::StageInstance);
			this->unk20C = psVar2;
		}
		pgVar1 = this->m_fileData->getData(Data_Type_Misc,0x1e,0xfffe);
		if (pgVar1 != 0) {
			psVar2 = stDataMultiContainer::create(pgVar1,Heaps::StageInstance);
			this->unk210 = psVar2;
		}
		pgVar1 = this->m_fileData->getData(Data_Type_Misc,0x28,0xfffe);
		if (pgVar1 != 0) {
			psVar2 = stDataMultiContainer::create(pgVar1,Heaps::StageInstance);
			this->unk214 = psVar2;
		}
		pgVar1 = this->m_fileData->getData(Data_Type_Misc,0x32,0xfffe);
		if (pgVar1 != 0) {
			psVar2 = stDataMultiContainer::create(pgVar1,Heaps::StageInstance);
			this->unk218 = psVar2;
		}
		pgVar1 = this->m_fileData->getData(Data_Type_Misc,0x3c,0xfffe);
		if (pgVar1 != 0) {
			psVar2 = stDataMultiContainer::create(pgVar1,Heaps::StageInstance);
			this->unk21C = psVar2;
		}
		pgVar1 = this->m_fileData->getData(Data_Type_Misc,0x46,0xfffe);
		if (pgVar1 != 0) {
			psVar2 = stDataMultiContainer::create(pgVar1,Heaps::StageInstance);
			this->unk220 = psVar2;
		}
		pgVar1 = this->m_fileData->getData(Data_Type_Misc,0x50,0xfffe);
		if (pgVar1 != 0) {
			psVar2 = stDataMultiContainer::create(pgVar1,Heaps::StageInstance);
			this->unk224 = psVar2;
		}
		pgVar1 = this->m_fileData->getData(Data_Type_Misc,0x5a,0xfffe);
		if (pgVar1 != 0) {
			psVar2 = stDataMultiContainer::create(pgVar1,Heaps::StageInstance);
			this->unk228 = psVar2;
		}
		pgVar1 = this->m_fileData->getData(Data_Type_Misc,0x64,0xfffe);
		if (pgVar1 != 0) {
			psVar2 = stDataMultiContainer::create(pgVar1,Heaps::StageInstance);
			this->unk22C = psVar2;
		}
		pgVar1 = this->m_fileData->getData(Data_Type_Misc,0x6e,0xfffe);
		if (pgVar1 != 0) {
			psVar2 = stDataMultiContainer::create(pgVar1,Heaps::StageInstance);
			this->unk230 = psVar2;
		}
		pgVar1 = this->m_fileData->getData(Data_Type_Misc,0x78,0xfffe);
		if (pgVar1 != 0) {
			psVar2 = stDataMultiContainer::create(pgVar1,Heaps::StageInstance);
			this->unk234 = psVar2;
		}
		pgVar1 = this->m_fileData->getData(Data_Type_Misc,0x82,0xfffe);
		if (pgVar1 != 0) {
			psVar2 = stDataMultiContainer::create(pgVar1,Heaps::StageInstance);
			this->unk238 = psVar2;
		}
		pgVar1 = this->m_fileData->getData(Data_Type_Misc,0x8c,0xfffe);
		if (pgVar1 != 0) {
			psVar2 = stDataMultiContainer::create(pgVar1,Heaps::StageInstance);
			this->unk23C = psVar2;
		}
		pgVar1 = this->m_fileData->getData(Data_Type_Misc,0x96,0xfffe);
		if (pgVar1 != 0) {
			psVar2 = stDataMultiContainer::create(pgVar1,Heaps::StageInstance);
			this->unk240 = psVar2;
		}
		pgVar1 = this->m_fileData->getData(Data_Type_Misc,0xa0,0xfffe);
		if (pgVar1 != 0) {
			psVar2 = stDataMultiContainer::create(pgVar1,Heaps::StageInstance);
			this->unk244 = psVar2;
		}
		pgVar1 = this->m_fileData->getData(Data_Type_Misc,0xaa,0xfffe);
		if (pgVar1 != 0) {
			psVar2 = stDataMultiContainer::create(pgVar1,Heaps::StageInstance);
			this->unk248 = psVar2;
		}
		pgVar1 = this->m_fileData->getData(Data_Type_Misc,0xb4,0xfffe);
		if (pgVar1 != 0) {
			psVar2 = stDataMultiContainer::create(pgVar1,Heaps::StageInstance);
			this->unk24C = psVar2;
		}
		pgVar1 = this->m_fileData->getData(Data_Type_Misc,0xbe,0xfffe);
		if (pgVar1 != 0) {
			psVar2 = stDataMultiContainer::create(pgVar1,Heaps::StageInstance);
			this->unk250 = psVar2;
		}
		pgVar1 = this->m_fileData->getData(Data_Type_Misc,0xc8,0xfffe);
		if (pgVar1 != 0) {
			psVar2 = stDataMultiContainer::create(pgVar1,Heaps::StageInstance);
			this->unk254 = psVar2;
		}
		pgVar1 = this->m_fileData->getData(Data_Type_Misc,0xd2,0xfffe);
		if (pgVar1 != 0) {
			psVar2 = stDataMultiContainer::create(pgVar1,Heaps::StageInstance);
			this->unk258 = psVar2;
		}
		pgVar1 = this->m_fileData->getData(Data_Type_Misc,0xdc,0xfffe);
		if (pgVar1 != 0) {
			psVar2 = stDataMultiContainer::create(pgVar1,Heaps::StageInstance);
			this->unk25C = psVar2;
		}
		pgVar1 = this->m_fileData->getData(Data_Type_Misc,0xe6,0xfffe);
		if (pgVar1 != 0) {
			psVar2 = stDataMultiContainer::create(pgVar1,Heaps::StageInstance);
			this->unk260 = psVar2;
		}
		pgVar1 = this->m_fileData->getData(Data_Type_Misc,0xf0,0xfffe);
		if (pgVar1 != 0) {
			psVar2 = stDataMultiContainer::create(pgVar1,Heaps::StageInstance);
			this->unk264 = psVar2;
		}
		pgVar1 = this->m_fileData->getData(Data_Type_Misc,0xfa,0xfffe);
		if (pgVar1 != 0) {
			psVar2 = stDataMultiContainer::create(pgVar1,Heaps::StageInstance);
			this->unk268 = psVar2;
		}
		pgVar1 = this->m_fileData->getData(Data_Type_Misc,0x104,0xfffe);
		if (pgVar1 != 0) {
			psVar2 = stDataMultiContainer::create(pgVar1,Heaps::StageInstance);
			this->unk26C = psVar2;
		}
		pgVar1 = this->m_fileData->getData(Data_Type_Misc,0x10e,0xfffe);
		if (pgVar1 != 0) {
			psVar2 = stDataMultiContainer::create(pgVar1,Heaps::StageInstance);
			this->unk270 = psVar2;
		}
	}
	return;
}

void stPictchat::initPictIDList() { //initPict
	char uVar1;
	u32 uVar2;
	u8 uVar3;
	u8 uVar4;
	u32 dVar5;
	float fVar6;
	for (uVar4 = 0; uVar4 < 27; uVar4++) {
		this->pictIDList[uVar4] = uVar4 + 1;	
	}
	dVar5 = 0x0;
	//uVar4 = 0;
	for (uVar4 = 0; uVar4 < 27; uVar4++) {
		fVar6 = randf();
		uVar2 = uVar4;
		//uVar4++;
		uVar1 = this->pictIDList[uVar2];
		uVar3 = ((27-dVar5) * fVar6);
		this->pictIDList[uVar2] = this->pictIDList[uVar3];
		this->pictIDList[uVar3] = uVar1;
	}
	return;
}