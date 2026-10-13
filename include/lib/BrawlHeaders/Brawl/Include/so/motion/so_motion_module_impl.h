#pragma once

#include <StaticAssert.h>
#include <memory.h>
#include <mt/mt_vector.h>
#include <so/anim/so_anim_chr.h>
#include <so/so_array.h>
#include <so/event/so_event_presenter.h>
#include <so/status/so_status_event_presenter.h>
#include <so/motion/so_motion_event_presenter.h>
#include <so/model/so_model_event_presenter.h>
#include <so/anim/so_anim_cmd_event_presenter.h>
#include <so/transition/so_transition_module_impl.h>
#include <types.h>

class soModuleAccesser;

class soMotionChangeParam {
public:
    int m_kind;
    float m_frame;
    float m_rate;
    u8 _12;
    u8 _13;
    u8 _14;
    u8 _15;
};
static_assert(sizeof(soMotionChangeParam) == 16, "Class is wrong size!");

class soMotionModule {
public:
    // TODO: verify params
    virtual ~soMotionModule();
    virtual void activate();
    virtual void deactivate();
    virtual void setData(void*);
    virtual void updateFrame(float);
    virtual void updateNode();
    virtual float getRate();
    virtual void setRate(float rate);
    virtual void setLoopFlag(bool loopFlag);
    virtual bool isLoopFlag();
    virtual void setFrame(float frame);
    virtual void setFrameSyncAnimCmd(float frame);
    virtual float getFrame();
    virtual bool isAnimResFile(int kind);
    virtual float getEndFrame(int kind);
    virtual float getEndFrame();
    virtual bool isEnd();
    virtual bool isLooped();
    virtual bool isAnimCmd(int);
    virtual char* getName(int kind, bool);
    virtual char* getName();
    virtual int getKind();
    virtual float getWeight();
    virtual float getPrevWeight();
    virtual void setWeight(float weight);
    virtual void setWeightRate(float weightRate);
    virtual bool isBlend();
    virtual void disableNode(int);
    virtual void calcNode(void*, int, int);
    virtual void calcNode(int, void*, void*);
    virtual bool changeMotionRequest(soMotionChangeParam* changeParam);
    virtual void processFixPosition();
    virtual void processFixCamera();
    virtual void add2ndAnimChr(float, float, int kind, bool);
    virtual void remove2ndAnimChr();
    virtual void set2ndRate(float rate);
    virtual float get2ndFrame();
    virtual int get2ndKind();
    virtual bool is2ndEnd();
    virtual void addPartialAnimChr(float, float, void*, void*, int, int, int);
    virtual void removePartialAnimChr(int);
    virtual void compRemovePartialAnimChr(int);
    virtual void detachPartialAnimChr(u32, bool);
    virtual void attachPartialAnimChr(u32);
    virtual int getPartialSize();
    virtual int getPartialKind(int);
    virtual void setPartialRate(float rate, int);
    virtual float getPartialRate(int);
    virtual void setPartialFrame(float frame, int);
    virtual void setPartialFrameSyncAnimCmd(float frame, int);
    virtual float getPartialFrame(int);
    virtual float getPartialEndFrame(int);
    virtual bool isEndPartial(int);
    virtual bool isLoopedPartial(int);
    virtual int getOtherAnimSize();
    virtual int getOtherAnimKind(int);
    virtual void addOtherAnim(float, float, int, u32, bool);
    virtual void addOtherAnim(float, float, int, int, int, bool);
    virtual void removeOtherAnim(int);
    virtual void setOtherAnimRate(float rate, int);
    virtual float getOtherAnimRate(int);
    virtual void setOtherAnimFrame(float frame, int);
    virtual float getOtherAnimFrame(int);
    virtual float getOtherAnimEndFrame(int);
    virtual bool isEndOtherAnim(int);
    virtual bool isLoopedOtherAnim(int);
    virtual float getTransNTranslateEndFrame(void*, int kind);
    virtual Vec3f getTransNTranslate();
    virtual void updateTransMoveSpeed();
    virtual bool isTransMove(float);
    virtual Vec3f getTransMoveSpeed();
    virtual Vec3f get2ndTransNTranslate();
    virtual void update2ndTransMoveSpeed();
    virtual bool is2ndTransMove();
    virtual Vec3f get2ndTransMoveSpeed();
    virtual Vec3f getBlendTransMoveSpeed();
    virtual int getNum();
    virtual void setShareAdjustNode(float, void*);
    virtual void setPartialCancelNodeData(void*);
    virtual void enablePartialCancelNode(bool);
    virtual Vec3f getNodeRotate(int nodeId);
    virtual Vec3f getNodeTranslate(int nodeId, bool);
    virtual Vec3f getNodeTranslate(float, int kind, int nodeId, bool);
    virtual void begin();
    virtual void rewind();
    virtual void turnBack();
    virtual bool checkTransition(int);
    virtual void addDefaultTransitionTerm(void*, int numTerms);
    virtual void addTransitionTerm(void*, int numTerms, int);
    virtual void setShareCancelNode(int, int);
    virtual void setOnlyChr(bool);
    virtual void* getLastMotionTransitionInfo();
    virtual void cacheAnimChrForce(int kind);
    virtual void setAnimObjCacheModule(void*);
    virtual void setCheckTexBind(); // TODO
    virtual void* detachAnmObjChrBlend();
    virtual void setAnmObjChrBlend(void*);
    virtual void setResourceId(int, int);
    virtual void clearResourceId();
    virtual void setKindOffset(int kindOffset);
    virtual void setShareAnimObjKind(int shareAnimObjKind);
    virtual void setShareAnimObjPartialInfo(int, int);
    virtual void setNoComp(bool);
    virtual void setTransMoveSpeedNoScale(bool);
    virtual bool isProcessFixPositionDone();
    virtual bool isForceImmediatelyStatusInterpret();
    virtual void changeMotion(soMotionChangeParam* changeParam);
};
static_assert(sizeof(soMotionModule) == 4, "Class is wrong size!");

class soMotionModuleImpl : public soMotionModule, public soStatusEventObserver, public soAnimCmdEventObserver, public soModelEventObserver, public soEventPresenter<soMotionEventObserver> {
public:

    // 52
    char _spacer1[4];

    // 56
    int m_kindOffset;

    // 60
    soAnimChr m_mainAnim;

    // 88
    int m_kind;

    // 92
    float m_weight;

    // 96
    float m_prevWeight;

    // 100
    char _100[4];

    // 104
    float m_weightRate;

    // 108
    soAnimChr m_secondaryAnim;

    // 136
    int m_secondaryKind;

    // 140
    char _spacer3[100];

    // 240
    soTransitionModule* m_transitionModule;

    // 244
    soArrayVector<soMotionChangeParam, 4> m_motionChangeParamArray;

    // 320
    char _spacer4[40];

    // 360
    soModuleAccesser* m_moduleAccesser;

    // 364
    char _spacer5[4];

    // TODO: verify params
    virtual ~soMotionModuleImpl();
    virtual void activate();
    virtual void deactivate();
    virtual void setData(void*);
    virtual void updateFrame(float);
    virtual void updateNode();
    virtual float getRate();
    virtual void setRate(float rate);
    virtual void setLoopFlag(bool loopFlag);
    virtual bool isLoopFlag();
    virtual void setFrame(float frame);
    virtual void setFrameSyncAnimCmd(float frame);
    virtual float getFrame();
    virtual bool isAnimResFile(int kind);
    virtual float getEndFrame(int kind);
    virtual float getEndFrame();
    virtual bool isEnd();
    virtual bool isLooped();
    virtual bool isAnimCmd(int);
    virtual char* getName(int kind, bool);
    virtual char* getName();
    virtual int getKind();
    virtual float getWeight();
    virtual float getPrevWeight();
    virtual void setWeight(float weight);
    virtual void setWeightRate(float weightRate);
    virtual bool isBlend();
    virtual void disableNode(int);
    virtual void calcNode(void*, int, int);
    virtual void calcNode(int, void*, void*);
    virtual bool changeMotionRequest(soMotionChangeParam* changeParam);
    virtual void processFixPosition();
    virtual void processFixCamera();
    virtual void add2ndAnimChr(float, float, int kind, bool);
    virtual void remove2ndAnimChr();
    virtual void set2ndRate(float rate);
    virtual float get2ndFrame();
    virtual int get2ndKind();
    virtual bool is2ndEnd();
    virtual void addPartialAnimChr(float, float, void*, void*, int, int, int);
    virtual void removePartialAnimChr(int);
    virtual void compRemovePartialAnimChr(int);
    virtual void detachPartialAnimChr(u32, bool);
    virtual void attachPartialAnimChr(u32);
    virtual int getPartialSize();
    virtual int getPartialKind(int);
    virtual void setPartialRate(float rate, int);
    virtual float getPartialRate(int);
    virtual void setPartialFrame(float frame, int);
    virtual void setPartialFrameSyncAnimCmd(float frame, int);
    virtual float getPartialFrame(int);
    virtual float getPartialEndFrame(int);
    virtual bool isEndPartial(int);
    virtual bool isLoopedPartial(int);
    virtual int getOtherAnimSize();
    virtual int getOtherAnimKind(int);
    virtual void addOtherAnim(float, float, int, u32, bool);
    virtual void addOtherAnim(float, float, int, int, int, bool);
    virtual void removeOtherAnim(int);
    virtual void setOtherAnimRate(float rate, int);
    virtual float getOtherAnimRate(int);
    virtual void setOtherAnimFrame(float frame, int);
    virtual float getOtherAnimFrame(int);
    virtual float getOtherAnimEndFrame(int);
    virtual bool isEndOtherAnim(int);
    virtual bool isLoopedOtherAnim(int);
    virtual float getTransNTranslateEndFrame(void*, int kind);
    virtual Vec3f getTransNTranslate();
    virtual void updateTransMoveSpeed();
    virtual bool isTransMove(float);
    virtual Vec3f getTransMoveSpeed();
    virtual Vec3f get2ndTransNTranslate();
    virtual void update2ndTransMoveSpeed();
    virtual bool is2ndTransMove();
    virtual Vec3f get2ndTransMoveSpeed();
    virtual Vec3f getBlendTransMoveSpeed();
    virtual int getNum();
    virtual void setShareAdjustNode(float, void*);
    virtual void setPartialCancelNodeData(void*);
    virtual void enablePartialCancelNode(bool);
    virtual Vec3f getNodeRotate(int nodeId);
    virtual Vec3f getNodeTranslate(int nodeId, bool);
    virtual Vec3f getNodeTranslate(float, int kind, int nodeId, bool);
    virtual void begin();
    virtual void rewind();
    virtual void turnBack();
    virtual bool checkTransition(int);
    virtual void addDefaultTransitionTerm(void*, int numTerms);
    virtual void addTransitionTerm(void*, int numTerms, int);
    virtual void setShareCancelNode(int, int);
    virtual void setOnlyChr(bool);
    virtual void* getLastMotionTransitionInfo();
    virtual void cacheAnimChrForce(int kind);
    virtual void setAnimObjCacheModule(void*);
    virtual void setCheckTexBind(); // TODO
    virtual void* detachAnmObjChrBlend();
    virtual void setAnmObjChrBlend(void*);
    virtual void setResourceId(int, int);
    virtual void clearResourceId();
    virtual void setKindOffset(int kindOffset);
    virtual void setShareAnimObjKind(int shareAnimObjKind);
    virtual void setShareAnimObjPartialInfo(int, int);
    virtual void setNoComp(bool);
    virtual void setTransMoveSpeedNoScale(bool);
    virtual bool isProcessFixPositionDone();
    virtual bool isForceImmediatelyStatusInterpret();
    virtual void changeMotion(soMotionChangeParam* changeParam);

    virtual void* getResFileData(int);
    virtual bool isObserv(char unk1);
    virtual bool notifyEventAnimCmd(acAnimCmd* acmd, soModuleAccesser* moduleAccesser, int unk3);
    virtual void notifyEventChangeStatus(int statusKind, int prevStatusKind, soStatusData* statusData, soModuleAccesser* moduleAccesser);
    virtual void notifyEventConstructInstance(bool, soModuleAccesser* moduleAccesser);
    virtual void notifyEventDestructInstance(soModuleAccesser* moduleAccesser);
};
static_assert(sizeof(soMotionModuleImpl) == 368, "Class is wrong size!");
