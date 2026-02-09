#include <gf/gf_3d_scene.h>
#include <mt/mt_matrix.h>
#include <mt/mt_vector.h>
#include <nw4r/g3d/g3d_resmdl.h>
#include <nw4r/g3d/g3d_resnode.h>
#include <nw4r/g3d/g3d_scnmdlsmpl.h>
#include <nw4r/g3d/g3d_scnmdl.h>
#include <so/model/so_model_module_simple.h>
#include <types.h>
#include <ut/ut_nw.h>

static inline gfSceneRoot* getRoot() {
    return g_gfSceneRoot;
}

soModelModuleSimple::soModelModuleSimple() : m_scnMdl(nullptr) { }

soModelModuleSimple::~soModelModuleSimple() { }

void soModelModuleSimple::setScnMdl(nw4r::g3d::ScnMdl* mdl, void*,
        gfSceneRoot::LayerType lt) {
    m_scnMdl = mdl;
    getRoot()->add(lt, getScnMdl());
}

nw4r::g3d::ScnMdl* soModelModuleSimple::detachScnMdl(void*) {
    nw4r::g3d::ScnMdl* mdl = getScnMdl();
    getRoot()->remove(mdl);
    m_scnMdl = nullptr;
    return mdl;
}

void soModelModuleSimple::resetLayerType(gfSceneRoot::LayerType lt) {
    if (getScnMdl() &&
            getRoot()->remove(getScnMdl()) &&
            getRoot()->add(lt, getScnMdl())) {
        m_layerType = lt;
    }
}

int soModelModuleSimple::getNodeId(const char* nodeName) {
    if (getScnMdl()) {
        nw4r::g3d::ResMdl resMdl = getScnMdl()->m_resMdl;
        nw4r::g3d::ResNode nd = resMdl.GetResNode(nodeName);
        if (nd.IsValid()) {
            return nd.IsValid() ? nd->m_nodeIndex : 0;
        }
    }
    return -1;
}

const char* soModelModuleSimple::getNodeName(u32 p1) {
    if (getScnMdl()) {
        nw4r::g3d::ResMdl resMdl = getScnMdl()->m_resMdl;
        if (p1 >= resMdl.GetResNodeNumEntries()) {
            return nullptr;
        }
        const nw4r::g3d::ResNodeData* nd = resMdl.GetResNode(p1).ptr();
        if (!nd) {
            goto end;
        }
        if (nd->m_nodeNameStrOffset) {
            return reinterpret_cast<const char*>(nd) +
                nd->m_nodeNameStrOffset;
        }
        return nullptr;
    }
end:
    return nullptr;
}

void soModelModuleSimple::getNodeGlobalMtx(u32 idx, Matrix* outMtx, bool) {
    getScnMdl()->GetScnMtxPos(outMtx, nw4r::g3d::ScnMdl::MTX_WORLD, idx);
}

Vec3f soModelModuleSimple::getNodeGlobalPosition(u32 correctNodeId, bool) {
    return nwSMGetGlobalPosition(getScnMdl(), correctNodeId);
}

Vec3f soModelModuleSimple::getNodeGlobalPosition(u32 correctNodeId, const Vec3f* pos, bool p3, bool p4) {
    return nwSMGetGlobalPosition(getScnMdl(), correctNodeId, pos);
}

Vec3f soModelModuleSimple::getNodeLocalPosition(u32 correctNodeId, bool p2) {
    return nwSMGetLocalPosition(getScnMdl(), correctNodeId);
}

void soModelModuleSimple::getNodeLocalMtxFromNode(u32 nodeId1, u32 nodeId2, Matrix* outMtx, bool) {
    Matrix stack68(true);
    Matrix stack38(true);
    Matrix stack8(true);
    getNodeGlobalMtx(nodeId2, &stack38, false);
    getNodeGlobalMtx(nodeId1, &stack68, false);

    stack68.inverse(&stack8);
    stack8.mul(&stack38, outMtx);
}

Vec3f soModelModuleSimple::getNodeGlobalRotation(u32 nodeId, bool p2) {
    return nwSMGetGlobalRotation(getScnMdl(), nodeId);
}

bool soModelModuleSimple::isNode(u32 id) {
    if (id != 0xFFFFFFFF && id < getNodeNum()) {
        return true;
    }
    return false;
}

u32 soModelModuleSimple::getNodeNum() const {
    nw4r::g3d::ResMdl resMdl = getScnMdl()->m_resMdl;
    return resMdl.GetResNodeNumEntries();
}

Vec3f soModelModuleSimple::getNodeGlobalOffsetFromTop(u32 nodeId) {
    Vec3f top = getNodeGlobalPosition(0, false);
    Vec3f nodePos = getNodeGlobalPosition(nodeId, false);
    Vec3f res;

    Vec3fSub(&res, &nodePos, &top);
    return res;
}

Vec3f soModelModuleSimple::getTopNodeGlobalPosFromNode(u32 nodeId, Vec3f* pos) {
    Vec3f topOffset = getNodeGlobalOffsetFromTop(nodeId);
    Vec3f res;

    Vec3fSub(&res, pos, &topOffset);
    return res;
}

bool soModelModuleSimple::setAnmObj(nw4r::g3d::AnmObj* obj) {
    if (getScnMdl()) {
        return getScnMdl()->SetAnmObj(obj, nw4r::g3d::ScnMdl::ANMOBJTYPE_NOT_SPECIFIED);
    }
    return false;
}

bool soModelModuleSimple::setOption(u32 option, u32 value) {
    if (getScnMdl()) {
        return getScnMdl()->SetScnObjOption(option, value);
    }
    return false;
}

bool soModelModuleSimple::getResMdl(nw4r::g3d::ResMdl* resMdl) {
    if (getScnMdl()) {
        *resMdl = getScnMdl()->m_resMdl;
        return true;
    }
    return false;
}

bool soModelModuleSimple::removeAnmObj(nw4r::g3d::ScnMdlSimple::AnmObjType type) {
    if (getScnMdl()) {
        return getScnMdl()->RemoveAnmObj(type) != nullptr;
    }
    return false;
}

void soModelModuleSimple::setVisibility(bool vis) {
    if (getScnMdl()) {
        nwSMSetVisibility(getScnMdl(), vis);
    }
}

void soModelModuleSimple::setNodeVisibility(u32 nodeId, bool vis) {
    if (getScnMdl()) {
        nwSMSetNodeVisibility(getScnMdl(), nodeId, vis);
    }
}

void soModelModuleSimple::setNodeVisibility(s32 numIds, const u32* nodeIds, bool vis) {
    if (getScnMdl()) {
        nwSMSetNodeVisibility(getScnMdl(), numIds, nodeIds, vis);
    }
}

void soModelModuleSimple::setDisposeInstanceImm(bool) { }
void soModelModuleSimple::setShadowNode(int) { }
Matrix* soModelModuleSimple::getWorldMtxArray() { return nullptr; }
void soModelModuleSimple::preShadowCalcView() { }
bool soModelModuleSimple::isRefFB() { return false; }
void soModelModuleSimple::switchEnvMap(bool) { }
bool soModelModuleSimple::isEnvMap() { return false; }
bool soModelModuleSimple::isAddEnvMapMat() { return false; }
void soModelModuleSimple::setVirtualNodeUpdate(u32 virtualNodeIndex, bool) { }
void soModelModuleSimple::initVirtualNode(int, u32, u32, void*, Matrix*) { }
void soModelModuleSimple::changeMaterialTex(soResourceModule*, const char* resMat, const char* resPlt, nw4r::g3d::ResFile) { }
void soModelModuleSimple::renderNodeAxis(u32 nodeIndex, float) { }
void soModelModuleSimple::setNodeVisibility(u32 nodeId, bool visibility, bool) { }
void soModelModuleSimple::setNodeVisibility(s32 numIds, const u32* nodeIds, bool visibility, bool) { }
void soModelModuleSimple::setVisibility(bool visibility, bool) { }
gfSceneRoot::LayerType soModelModuleSimple::getLayerType() { return m_layerType; }
void soModelModuleSimple::setScaleZ(float) { }
void soModelModuleSimple::setScale(float) { }
float soModelModuleSimple::getScale() { return 1.0f; }
Vec3f soModelModuleSimple::getResFileNodeRotation(u32 nodeIndex) { return Vec3f(0, 0, 0); }
Vec3f soModelModuleSimple::getResFileNodeTranslate(u32 nodeIndex) { return Vec3f(0, 0, 0); }
int soModelModuleSimple::getTransNNodeId() { return -1; }
const char* soModelModuleSimple::getTransNNodeName() { return nullptr; }
void soModelModuleSimple::setTransNNodeId(int) { }
u32 soModelModuleSimple::getNodeNum(bool) const { return 0; }
void soModelModuleSimple::setNodeGlobalMtx(u32 index, Matrix*, bool) { }
int soModelModuleSimple::getCorrectNodeId(u32) { return -1; }
void soModelModuleSimple::setNodeTranslate(u32, Vec3f* xlate) { }
Vec3f soModelModuleSimple::getNodeTranslate(u32 p1) { return Vec3f(0, 0, 0); }
void soModelModuleSimple::setNodeRotate(u32 , Vec3f* rot) { }
void soModelModuleSimple::setNodeRotateZ(u32 , float z) { }
void soModelModuleSimple::setNodeRotateY(u32 , float y) { }
void soModelModuleSimple::setNodeRotateX(u32 , float x) { }
Vec3f soModelModuleSimple::getNodeRotate(u32 nodeIndex) { return Vec3f(0, 0, 0); }
void soModelModuleSimple::setNodeScale(u32 , Vec3f* ) { }
Vec3f soModelModuleSimple::getNodeScale(u32 nodeIndex) { return Vec3f(1, 1, 1); }
void soModelModuleSimple::setNodeSRT(u32 , Vec3f* scale, Vec3f* rot, Vec3f* xlate) { }
void soModelModuleSimple::clearNodeSRT(u32 p1) { }
void soModelModuleSimple::clearNodeSetUp() { }
void soModelModuleSimple::setLockMtx(bool) { }
void soModelModuleSimple::setScnMdlExtern(nw4r::g3d::ScnMdl* p) { m_scnMdl = p; }
void soModelModuleSimple::setLoupeNo(s8) { }
s8 soModelModuleSimple::getLoupeNo() { static s8 val = 0xFF; return val; }
nw4r::g3d::ScnMdl* soModelModuleSimple::getScnMdl(bool) const { return nullptr; }
void soModelModuleSimple::begin(bool) { }
void soModelModuleSimple::activate() { }
void soModelModuleSimple::deactivate() { }
void soModelModuleSimple::destructInstance() { }
void soModelModuleSimple::constructInstance(gfSceneRoot::LayerType, u32 flags,
        bool, s8, nw4r::g3d::ResFile, const char*, const char*, s16 mdlResId,
        void*, u8 loupeNo, int priorityDrawXlu) { }
void soModelModuleSimple::clearSetUpMtx() { }
void soModelModuleSimple::setUpSkinningMtx() { }
void soModelModuleSimple::setUpMtx(u32 nodeId) { }
void soModelModuleSimple::setUpMtx(u32* nodeIds, s32 numNodeIds) { }
void soModelModuleSimple::setUpMtxFinal() { }
