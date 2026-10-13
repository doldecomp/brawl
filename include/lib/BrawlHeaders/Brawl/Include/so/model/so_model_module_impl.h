#pragma once

#include <StaticAssert.h>
#include <memory.h>
#include <mt/mt_matrix.h>
#include <mt/mt_vector.h>
#include <so/model/so_model_module_simple.h>
#include <so/model/so_model_virtual_node.h>
#include <so/event/so_event_presenter.h>
#include <so/model/so_model_event_presenter.h>
#include <so/anim/so_anim_cmd_event_presenter.h>
#include <types.h>

class soModuleAccesser;

class soModelModuleImpl : public soModelModuleSimple, public soAnimCmdEventObserver, public soEventPresenter<soModelEventObserver> {
    char _spacer1[156];
    soModuleAccesser* m_moduleAccesser; // +0xC8
public:
    soModelModuleImpl(soModuleAccesser* acc,
                      soArray<soModelNodeSetUp>* nodeSetUps,
                      void* extendNodeTbl,
                      soArray<soModelVirtualNode>* virtualNodes,
                      soEventObserverRegistrationDesc* regDesc,
                      float f1);
    // TODO: Verify Params
    virtual void setUpMtx(u32 nodeId);
    virtual void setUpMtx(u32* nodeIds, s32 numNodeIds);
    virtual void setUpMtxFinal();
    virtual void setUpSkinningMtx();
    virtual void clearSetUpMtx();
    virtual void constructInstance(gfSceneRoot::LayerType, u32 flags, bool, s8, nw4r::g3d::ResFile, const char*, const char*, s16 mdlResId, void*, u8 loupeNo, int
                                   priorityDrawXlu);
    virtual void destructInstance();
    virtual void activate();
    virtual void deactivate();
    virtual void begin(bool);
    virtual nw4r::g3d::ScnMdl* getScnMdl(bool) const;
    virtual void setScnMdl(nw4r::g3d::ScnMdl*, void*, gfSceneRoot::LayerType);
    virtual void setScnMdlExtern(nw4r::g3d::ScnMdl *);
    virtual nw4r::g3d::ScnMdl* detachScnMdl(void*);
    virtual void setLockMtx(bool);
    virtual void clearNodeSetUp();
    virtual void clearNodeSRT(u32 p1);
    virtual void setNodeSRT(u32 , Vec3f* scale, Vec3f* rot, Vec3f* xlate);
    virtual Vec3f getNodeScale(u32 nodeIndex);
    virtual void setNodeScale(u32 , Vec3f* );
    virtual Vec3f getNodeRotate(u32 nodeIndex);
    virtual void setNodeRotateX(u32 , float x);
    virtual void setNodeRotateY(u32 , float y);
    virtual void setNodeRotateZ(u32 , float z);
    virtual void setNodeRotate(u32 , Vec3f* rot);
    virtual Vec3f getNodeTranslate(u32 p1);
    virtual void setNodeTranslate(u32 , Vec3f* xlate);
    virtual int getCorrectNodeId(u32);
    virtual Vec3f getNodeGlobalPosition(u32 correctNodeId, bool );
    virtual Vec3f getNodeGlobalPosition(u32 correctNodeId, const Vec3f* p2, bool, bool );
    virtual Vec3f getNodeLocalPosition(u32 correctNodeId, bool );
    virtual void getNodeLocalMtxFromNode(u32 node1, u32 node2, Matrix* outMtx, bool );
    virtual void getNodeGlobalMtx(u32 index, Matrix* outMtx, bool ) const;
    virtual void setNodeGlobalMtx(u32 index, Matrix* , bool );
    virtual Vec3f getNodeGlobalRotation(u32 nodeIndex, bool );
    virtual bool isNode(u32 id);
    virtual u32 getNodeNum(bool) const;
    virtual void setTransNNodeId(int);
    virtual const char *getTransNNodeName();
    virtual int getTransNNodeId();
    virtual Vec3f getResFileNodeTranslate(u32 nodeIndex);
    virtual Vec3f getResFileNodeRotation(u32 nodeIndex);
    virtual void renderNodeAxis(u32 nodeIndex, float );
    virtual float getScale();
    virtual void setScale(float);
    virtual void setScaleZ(float);
    virtual gfSceneRoot::LayerType getLayerType();
    virtual s8 getLoupeNo();
    virtual void setLoupeNo(s8);
    virtual void setVisibility(bool visibility, bool);
    virtual void setNodeVisibility(u32 nodeId, bool visibility, bool);
    virtual void setNodeVisibility(s32 numIds, const u32* nodeIds, bool visibility, bool);
    virtual void changeMaterialTex(soResourceModule*, const char*resMat, const char*resPlt, nw4r::g3d::ResFile);
    virtual void initVirtualNode(int, u32, u32, void*, Matrix*);
    virtual void setVirtualNodeUpdate(u32 virtualNodeIndex, bool);
    virtual bool isAddEnvMapMat();
    virtual bool isEnvMap();
    virtual void switchEnvMap(bool);
    virtual bool isRefFB();
    virtual void preShadowCalcView();
    virtual Matrix *getWorldMtxArray();
    virtual void setShadowNode(int);
    virtual void setDisposeInstanceImm(bool);
    virtual ~soModelModuleImpl();

    virtual bool isObserv(char unk1);
    virtual bool notifyEventAnimCmd(acAnimCmd* acmd, soModuleAccesser* moduleAccesser, int unk3);
};
static_assert(sizeof(soModelModuleImpl) == 204, "Class is wrong size!");

class soModelModuleImplVariable : public soModelModuleImpl {
    u32** unkCC;
public:
    soModelModuleImplVariable(soModuleAccesser* acc,
                              soArray<soModelNodeSetUp>* nodeSetUps,
                              void* extendNodeTbl,
                              soArray<soModelVirtualNode>* virtualNodes,
                              soEventObserverRegistrationDesc* regDesc,
                              float f1);
    virtual void setUpMtx(u32* nodeIds, s32 numNodeIds);
    virtual void clearNodeSRT(u32 p1);
    virtual void setNodeSRT(u32 , Vec3f* scale, Vec3f* rot, Vec3f* xlate);
    virtual Vec3f getNodeScale(u32 nodeIndex);
    virtual void setNodeScale(u32 , Vec3f* );
    virtual Vec3f getNodeRotate(u32 nodeIndex);
    virtual void setNodeRotateX(u32 , float x);
    virtual void setNodeRotateY(u32 , float y);
    virtual void setNodeRotateZ(u32 , float z);
    virtual void setNodeRotate(u32 , Vec3f* rot);
    virtual Vec3f getNodeTranslate(u32 p1);
    virtual void setNodeTranslate(u32 , Vec3f* xlate);
    virtual int getNodeId(const char *nodeName);
    virtual int getCorrectNodeId(u32);
    virtual int getRealNodeId(u32) const;
    virtual const char* getNodeName(u32 p1);
    virtual Vec3f getNodeGlobalPosition(u32 correctNodeId, bool );
    virtual Vec3f getNodeGlobalPosition(u32 correctNodeId, const Vec3f* p2, bool, bool );
    virtual Vec3f getNodeLocalPosition(u32 correctNodeId, bool );
    virtual void getNodeLocalMtxFromNode(u32 node1, u32 node2, Matrix* outMtx, bool );
    virtual void getNodeGlobalMtx(u32 index, Matrix* outMtx, bool ) const;
    virtual void setNodeGlobalMtx(u32 index, Matrix* , bool );
    virtual Vec3f getNodeGlobalRotation(u32 nodeIndex, bool );
    virtual bool isNode(u32 id);
    virtual Vec3f getResFileNodeTranslate(u32 nodeIndex);
    virtual Vec3f getResFileNodeRotation(u32 nodeIndex);
    virtual Vec3f getNodeGlobalOffsetFromTop(u32 p1);
    virtual Vec3f getTopNodeGlobalPosFromNode(u32 p1, Vec3f* p2);
    virtual void renderNodeAxis(u32 nodeIndex, float );
    virtual void setNodeVisibility(u32 nodeId, bool visibility, bool);
    virtual void setNodeVisibility(s32 numIds, const u32* nodeIds, bool visibility, bool);
    virtual void setNodeConvertData(u32** convertData);
    virtual ~soModelModuleImplVariable();
};
static_assert(sizeof(soModelModuleImplVariable) == 0xD0, "Class is wrong size!");
