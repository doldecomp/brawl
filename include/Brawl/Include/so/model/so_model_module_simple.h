#pragma once

#include <StaticAssert.h>
#include <mt/mt_matrix.h>
#include <mt/mt_vector.h>
#include <gf/gf_3d_scene.h>
#include <so/resource/so_resource_module_impl.h>
#include <nw4r/g3d/g3d_resfile.h>
#include <nw4r/g3d/g3d_scnmdlsmpl.h>
#include <nw4r/g3d/g3d_scnmdl.h>
#include <nw4r/math/math_types.h>
#include <mt/mt_vector.h>
#include <so/so_null.h>
#include <types.h>

class soModelModule : private soNull, public soNullable {
public:
    soModelModule() { }

    // TODO: Verify Params
    virtual void setUpMtx(u32 nodeId) = 0;
    virtual void setUpMtx(u32* nodeIds, s32 numNodeIds) = 0;
    virtual void setUpMtxFinal() = 0;
    virtual void setUpSkinningMtx() = 0;
    virtual void clearSetUpMtx() = 0;
    virtual void constructInstance(gfSceneRoot::LayerType, u32 flags, bool, s8, nw4r::g3d::ResFile, const char*, const char*, s16 mdlResId, void*, u8 loupeNo, int
                                   priorityDrawXlu) = 0;
    virtual void destructInstance() = 0;
    virtual void activate() = 0;
    virtual void deactivate() = 0;
    virtual void begin(bool) = 0;
    virtual nw4r::g3d::ScnMdl* getScnMdl() const = 0;
    virtual nw4r::g3d::ScnMdl* getScnMdl(bool) const = 0;
    virtual void setScnMdl(nw4r::g3d::ScnMdl*, void*, gfSceneRoot::LayerType) = 0;
    virtual void setScnMdlExtern(nw4r::g3d::ScnMdl *) = 0;
    virtual nw4r::g3d::ScnMdl* detachScnMdl(void*) = 0;
    virtual void resetLayerType(gfSceneRoot::LayerType lt) = 0;
    virtual void setLockMtx(bool) = 0;
    virtual void clearNodeSetUp() = 0;
    virtual void clearNodeSRT(u32 p1) = 0;
    virtual void setNodeSRT(u32 , Vec3f* scale, Vec3f* rot, Vec3f* xlate) = 0;
    virtual Vec3f getNodeScale(u32 nodeIndex) = 0;
    virtual void setNodeScale(u32 , Vec3f* ) = 0;
    virtual Vec3f getNodeRotate(u32 nodeIndex) = 0;
    virtual void setNodeRotateX(u32 , float x) = 0;
    virtual void setNodeRotateY(u32 , float y) = 0;
    virtual void setNodeRotateZ(u32 , float z) = 0;
    virtual void setNodeRotate(u32 , Vec3f* rot) = 0;
    virtual Vec3f getNodeTranslate(u32 p1) = 0;
    virtual void setNodeTranslate(u32 , Vec3f* xlate) = 0;
    virtual int getNodeId(const char *nodeName) = 0;
    virtual int getCorrectNodeId(u32) = 0;
    virtual int getRealNodeId(u32) const = 0;
    virtual const char* getNodeName(u32 p1) = 0;
    virtual Vec3f getNodeGlobalPosition(u32 correctNodeId, bool ) = 0;
    virtual Vec3f getNodeGlobalPosition(u32 correctNodeId, const Vec3f* p2, bool, bool ) = 0;
    virtual Vec3f getNodeLocalPosition(u32 correctNodeId, bool ) = 0;
    virtual void getNodeLocalMtxFromNode(u32 node1, u32 node2, Matrix* outMtx, bool ) = 0;
    virtual void getNodeGlobalMtx(u32 idx, Matrix* outMtx, bool) const = 0;
    virtual void setNodeGlobalMtx(u32 index, Matrix* , bool ) = 0;
    virtual Vec3f getNodeGlobalRotation(u32 nodeIndex, bool ) = 0;
    virtual bool isNode(u32 id) = 0;
    virtual u32 getNodeNum() const = 0;
    virtual u32 getNodeNum(bool) const = 0;
    virtual void setTransNNodeId(int) = 0;
    virtual const char *getTransNNodeName() = 0;
    virtual int getTransNNodeId() = 0;
    virtual Vec3f getResFileNodeTranslate(u32 nodeIndex) = 0;
    virtual Vec3f getResFileNodeRotation(u32 nodeIndex) = 0;
    virtual Vec3f getNodeGlobalOffsetFromTop(u32 p1) = 0;
    virtual Vec3f getTopNodeGlobalPosFromNode(u32 p1, Vec3f* p2) = 0;
    virtual void renderNodeAxis(u32 nodeIndex, float ) = 0;
    virtual float getScale() = 0;
    virtual void setScale(float) = 0;
    virtual void setScaleZ(float) = 0;
    virtual gfSceneRoot::LayerType getLayerType() = 0;
    virtual bool setAnmObj(nw4r::g3d::AnmObj* obj) = 0;
    virtual bool removeAnmObj(nw4r::g3d::ScnMdlSimple::AnmObjType type) = 0;
    virtual bool setOption(u32 option, u32 value) = 0;
    virtual bool getResMdl(nw4r::g3d::ResMdl* resMdl) = 0;
    virtual s8 getLoupeNo() = 0;
    virtual void setLoupeNo(s8) = 0;
    virtual void setVisibility(bool visibility) = 0;
    virtual void setVisibility(bool visibility, bool) = 0;
    virtual void setNodeVisibility(u32 nodeId, bool visibility) = 0;
    virtual void setNodeVisibility(u32 nodeId, bool visibility, bool) = 0;
    virtual void setNodeVisibility(s32 numIds, const u32* nodeIds, bool visibility) = 0;
    virtual void setNodeVisibility(s32 numIds, const u32* nodeIds, bool visibility, bool) = 0;
    virtual void changeMaterialTex(soResourceModule*, const char*resMat, const char*resPlt, nw4r::g3d::ResFile) = 0;
    virtual void initVirtualNode(int, u32, u32, void*, Matrix*) = 0;
    virtual void setVirtualNodeUpdate(u32 virtualNodeIndex, bool) = 0;
    virtual bool isAddEnvMapMat() = 0;
    virtual bool isEnvMap() = 0;
    virtual void switchEnvMap(bool) = 0;
    virtual bool isRefFB() = 0;
    virtual void preShadowCalcView() = 0;
    virtual Matrix *getWorldMtxArray() = 0;
    virtual void setNodeConvertData(u32** convertData) = 0;
    virtual void setShadowNode(int) = 0;
    virtual void setDisposeInstanceImm(bool) = 0;
    virtual ~soModelModule() { }
};

class soModelModuleSimple : public soModelModule {
    // 0xC
    nw4r::g3d::ScnMdl* m_scnMdl;

    // 0x10
    gfSceneRoot::LayerType m_layerType;
public:
    soModelModuleSimple();

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
    virtual nw4r::g3d::ScnMdl* getScnMdl() const; // 0x3C
    virtual nw4r::g3d::ScnMdl* getScnMdl(bool) const;
    virtual void setScnMdl(nw4r::g3d::ScnMdl*, void*, gfSceneRoot::LayerType);
    virtual void setScnMdlExtern(nw4r::g3d::ScnMdl *);
    virtual nw4r::g3d::ScnMdl* detachScnMdl(void*);
    virtual void resetLayerType(gfSceneRoot::LayerType lt);
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
    virtual int getNodeId(const char *nodeName);
    virtual int getCorrectNodeId(u32);
    virtual int getRealNodeId(u32) const;
    virtual const char* getNodeName(u32 p1);
    virtual Vec3f getNodeGlobalPosition(u32 correctNodeId, bool );
    virtual Vec3f getNodeGlobalPosition(u32 correctNodeId, const Vec3f* p2, bool, bool );
    virtual Vec3f getNodeLocalPosition(u32 correctNodeId, bool );
    virtual void getNodeLocalMtxFromNode(u32 node1, u32 node2, Matrix* outMtx, bool );
    virtual void getNodeGlobalMtx(u32 idx, Matrix* outMtx, bool) const;
    virtual void setNodeGlobalMtx(u32 index, Matrix* , bool );
    virtual Vec3f getNodeGlobalRotation(u32 nodeIndex, bool );
    virtual bool isNode(u32 id);
    virtual u32 getNodeNum() const;
    virtual u32 getNodeNum(bool) const;
    virtual void setTransNNodeId(int);
    virtual const char *getTransNNodeName();
    virtual int getTransNNodeId();
    virtual Vec3f getResFileNodeTranslate(u32 nodeIndex);
    virtual Vec3f getResFileNodeRotation(u32 nodeIndex);
    virtual Vec3f getNodeGlobalOffsetFromTop(u32 p1);
    virtual Vec3f getTopNodeGlobalPosFromNode(u32 p1, Vec3f* p2);
    virtual void renderNodeAxis(u32 nodeIndex, float );
    virtual float getScale();
    virtual void setScale(float);
    virtual void setScaleZ(float);
    virtual gfSceneRoot::LayerType getLayerType();
    virtual bool setAnmObj(nw4r::g3d::AnmObj* obj);
    virtual bool removeAnmObj(nw4r::g3d::ScnMdlSimple::AnmObjType type);
    virtual bool setOption(u32 option, u32 value);
    virtual bool getResMdl(nw4r::g3d::ResMdl* resMdl);
    virtual s8 getLoupeNo();
    virtual void setLoupeNo(s8);
    virtual void setVisibility(bool visibility);
    virtual void setVisibility(bool visibility, bool);
    virtual void setNodeVisibility(u32 nodeId, bool visibility);
    virtual void setNodeVisibility(u32 nodeId, bool visibility, bool);
    virtual void setNodeVisibility(s32 numIds, const u32* nodeIds, bool visibility);
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
    virtual void setNodeConvertData(u32** convertData);
    virtual void setShadowNode(int);
    virtual void setDisposeInstanceImm(bool);
    virtual ~soModelModuleSimple();
};
static_assert(sizeof(soModelModuleSimple) == 20, "Class is wrong size!");
