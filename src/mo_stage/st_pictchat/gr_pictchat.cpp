#include <StaticAssert.h>
#include <memory.h>
#include <types.h>
#include <ec/ec_mgr.h>
#include <gf/gf_archive.h>
#include <gf/gf_3d_scene.h>
#include <gm/gm_lib.h>
#include <gm/gm_global.h>
#include <gr/gr_yakumono.h>
#include <mt/mt_matrix.h>
#include <mt/mt_vector.h>
#include <nw4r/g3d/g3d_resfile.h>
#include <snd/snd_id.h>
#include <ms/ms_message.h>
#include <mu/menu.h>
#include <mt/mt_prng.h>

#include <st_pictchat/gr_pictchat.h>

static void wrapper(grPictchat* ths, s32 mdlIndex) {
	ths->setMdlIndex(mdlIndex);
}

grPictchat::grPictchat(const char* taskname) : grYakumono(taskname) {
	unk110 = 0;
	unk114 = 0;
	setupMelee();
}


grPictchat::~grPictchat() {}
grPictchatBg::~grPictchatBg() {}




grPictchatBg* grPictchatBg::create(int mdlIndex, const char *tgtNodeName, const char *taskName) {
	grPictchatBg *bg = new (Heaps::StageInstance) grPictchatBg(taskName);
	if (bg != 0) {
		//bg->grYakumono(taskName);
		bg->isMessageInit = false;
		bg->unk154 = 0;
		bg->setupMelee();
		bg->msgData = 0;
		bg->unk15C = 0;
		bg->selectedPlayerNo = 0xFF;
		bg->pictIDWork = 0;
		bg->unk168 = 0;
		bg->setMdlIndex(mdlIndex);
		bg->setTgtNode(tgtNodeName);
	}
	return bg;
}

void grPictchatBg::update(float param1) {
	this->grGimmick::update(param1);
	if (this->m_isUpdate != false) {
		this->updateJoint(param1);
		this->updateMessage(param1);
	}
}

void grPictchatBg::updateJoint(float param1) {
	u16 uVar1;
	grCollisionJoint *pgVar2;
	u32 uVar3;
	u8 nodeIndex;
	grCollision *collision;
	if (this->unk168) {
		uVar3 = 0;
		if (this->pictIDWork == 19) {
			uVar3 = 0x2000;
		}
		this->unk168->m_0x52 = uVar3;
	} else {
		collision = this->m_collision;
		if (collision == 0) {
			uVar1 = collision->m_jointLen;
			nodeIndex = 0;
			//pgVar2 = this;
			//pgVar2 = collision->getJoint(nodeIndex);
				//((pgVar2 == (grPictchatBg *)0x0 || ((pgVar2->_grYakumono)._grGimmick._ground.modelAnimNum != this))))) {
			while ((nodeIndex != uVar1 &&
			((pgVar2 = collision->getJoint(nodeIndex),
			pgVar2 == 0 || (pgVar2->m_ground != this))))) {// || (pgVar2 != this))) { || (this->m_modelAnimNum != 1)
				nodeIndex++;
			}
			if (nodeIndex != uVar1) {
				this->unk168 = pgVar2;
			}
		}
	}
	return;
}

void grPictchatBg::updateMessage(float param1) {
	Message* this_00;
	u32 uVar1;
	u32 uVar2;
	int iVar3;
	const char* pcVar4;
	u32 uVar5;
	u8 bVar6;
	u8 bVar7;
	gmGlobalModeMelee *pgVar8;
	int iVar9;
	float dVar10;
	float uVar12;
	double dVar11;
	float fVar12;
	char locald8[8];
	
	char** locale4;
	u32* locale8;
	void* austack;
	
	if (this->isMessageInit != true) {
		if (this->isMessageInit != false) {
			return;
		}
		this_00 = new Message(0x1e0,Heaps::StageInstance);
		this->message = this_00;
		if (this_00 == 0){
			return;
		}
		this_00->allocMsgBuf(0x400,1,Heaps::StageInstance);
		this_00->attachMsgBuf(0,this->m_sceneModels[0],"pictchat_font",1,3,0.0625);
		this->isMessageInit = true;
	}
	this->message->changeMsgBuf(0);
	this->message->clearMsgBuf();
	this->message->setWindow(-1700.0,0.0,1700.0,570.0);
	this->message->setFace(4);
	this->message->setFixedWidth(-1.0);
	this->message->setColor(-1);
	pgVar8 = g_GameGlobal->m_modeMelee;
	if (pgVar8 == 0) {
		return;
	}
	uVar5 = this->selectedPlayerNo;
	if (uVar5 == 0xff) {
		bVar7 = 0;
		bVar7 = 0;
		iVar9 = 7;
		do {
			locald8[bVar6] = 0xFF;
			if (pgVar8->m_playersInitData[bVar6].m_state !=3) {
				uVar5 = bVar7;
				bVar7 = bVar7 + 1;
				locald8[uVar5] = bVar6;
			}
			bVar6 = bVar6 + 1;
			iVar9 = iVar9 - 1;
		} while (iVar9 != 0);
		
		if (bVar7 == 0) {
			return;
		}
		fVar12 = randf();
		uVar1 = bVar7;
		uVar2 = uVar5;
		if (uVar2 < uVar1) {
			uVar1 = uVar2;
		}
		uVar5 = locald8[uVar1];
		this->selectedPlayerNo = locald8[uVar1];
		if (pgVar8->m_playersInitData[bVar6].m_state !=3) {
			return;
		}
	}
	
	//iVar9 = 0;
	iVar9 = muMenu::exchangeGmCharacterKind2MuStockchkind(pgVar8->m_playersInitData[uVar5].m_characterKind);
	if (iVar9 == 23) {
		iVar9 = 3;
	}
	
	uVar12 = 0.0;
	dVar10 = 20.0;
	
	dVar11 = 200.0;
	this->message->setScale(dVar10,dVar10);
	this->message->setCursorX(uVar12);
	this->message->setCursorY(dVar11);
	iVar3 = g_GameGlobal->getLanguage();
	if (iVar3 == 0) {
		this->message->getPrintIndexData(this->unk15C,13,locale4,locale8);
		//this->message->printf()
		if (7 < locale8[0]) {
			locale8[0] = 7;
		}
		//memcpy(austack,(void*)locale4,locale8)
		pcVar4 = muMenu::exchangeMuStockchkind2MuCharName(iVar9);
		this->message->printf(pcVar4);
	} else {
		pcVar4 = muMenu::exchangeMuStockchkind2MuCharName(iVar9);
		this->message->printf(pcVar4);
	}
}
//grPictchatBg::~grPictchatBg() {}