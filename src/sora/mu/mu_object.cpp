#include <gf/gf_heap_manager.h>
#include <gf/gf_model.h>
#include <nw4r/g3d/g3d_resfile.h>
#include <nw4r/g3d/g3d_resmdl.h>
#include <nw4r/g3d/g3d_scnmdl.h>
#include <mt/mt_matrix.h>
#include <mt/mt_vector.h>
#include <nw4r/math/math_arithmetic.h>
#include <ut/ut_nw.h>
#include <sr/sr_common.h>
#include <types.h>

// Animation frame policy function table (lives in gf_model_animation.cpp).
extern void* lbl_8059C648[2];

// "%s__%d"
extern char lbl_8059DF20[7];
extern "C" int sprintf(char* str, const char* fmt, ...);

// ResFile name lookups that are not declared in the BrawlHeaders ResFile class.
nw4r::g3d::ResAnmChr ResFile_GetResAnmChrByName(nw4r::g3d::ResFile* file, const char* name);
nw4r::g3d::ResAnmVis ResFile_GetResAnmVisByName(nw4r::g3d::ResFile* file, const char* name);
nw4r::g3d::ResAnmClr ResFile_GetResAnmClrByName(nw4r::g3d::ResFile* file, const char* name);
nw4r::g3d::ResAnmTexPat ResFile_GetResAnmTexPatByName(nw4r::g3d::ResFile* file, const char* name);
nw4r::g3d::ResAnmTexSrt ResFile_GetResAnmTexSrtByName(nw4r::g3d::ResFile* file, const char* name);

void ResNode_SetRotate(nw4r::g3d::ResNode* node, float x, float y, float z);
void ResNode_SetScale(nw4r::g3d::ResNode* node, float x, float y, float z);

struct ChrAnmResult {
    u32 m_flags;
    Vec3f m_scale;
    u8 m_10[0x40];
};
void ChrAnmResult_GetScale(const ChrAnmResult* res, Vec3f* out);

// The real CopiedMatAccess is 0x34 bytes; the BrawlHeaders copy is 4 bytes short.
struct MatAccess : public nw4r::g3d::ScnMdl::CopiedMatAccess {
    u32 m_pad;
    MatAccess(nw4r::g3d::ScnMdl* mdl, u32 id) : CopiedMatAccess(mdl, id) {}
};

nw4r::g3d::ResTexObjData* CopiedMatAccess_GetResTexObj(nw4r::g3d::ScnMdl::CopiedMatAccess* access, bool sync);
extern "C" void GXGetTexObjAll(const GXTexObj* obj, void** image, u16* w, u16* h, GXTexFmt* fmt, GXTexWrapMode* wrapS, GXTexWrapMode* wrapT, GXBool* mipmap);

void ScnMdl_SetNodeMtx(nw4r::g3d::ScnMdl* mdl, u32 nodeId, const Matrix* mtx);

class MuObject {
public:
    virtual ~MuObject();
    nw4r::g3d::ResFile m_resFile;    // 0x04
    nw4r::g3d::ResMdl m_resMdl;      // 0x08
    nw4r::g3d::ScnMdl* m_scnMdl;     // 0x0c
    nw4r::g3d::ScnMdl* m_sceneModel; // 0x10
    gfModelAnimation* m_modelAnim;   // 0x14
    u8 m_18[0x1c];                   // 0x18
    u32 m_baseNode;                  // 0x34
    u8 m_38[4];                      // 0x38
    Vec3f m_trans;                   // 0x3c
    Vec3f m_rot;                     // 0x48
    Heaps::HeapType m_heapType;      // 0x54
    u8 m_58[8];                      // 0x58

    MuObject(nw4r::g3d::ResFile* modelSource, const char* modelNode, int drawPriority, nw4r::g3d::ResFile* textureSource, bool isByName, Heaps::HeapType heapType);
    MuObject(nw4r::g3d::ResFile* modelSource, int animNode, int modelNode, nw4r::g3d::ResFile* textureSource, bool isByIndex, Heaps::HeapType heapType);

    static MuObject* create(nw4r::g3d::ResFile* modelSource, const char* modelNode, int drawPriority, nw4r::g3d::ResFile* textureSource, Heaps::HeapType type);
    static MuObject* create(nw4r::g3d::ResFile* modelSource, int modelNode, nw4r::g3d::ResFile* textureSource, int animNode, Heaps::HeapType type);

    static MuObject* createAlt(nw4r::g3d::ResFile* modelSource, const char* modelNode, int drawPriority, nw4r::g3d::ResFile* textureSource, Heaps::HeapType type);

    void changeNodeAnimN(const char* animName);
    bool changeNodeAnimNIf(const char* animName);
    void changeVisAnimN(const char* animName);
    bool changeVisAnimNIf(const char* animName);
    void changeTexPatAnim(u32 index);
    void changeTexPatAnimN(const char* animName);
    bool changeTexPatAnimNIf(const char* animName);
    void changeTexSrtAnimN(const char* animName);
    bool changeTexSrtAnimNIf(const char* animName);
    void changeClrAnimN(const char* animName);
    bool changeClrAnimNIf(const char* animName);
    void changeAnimN(const char* animName);
    u16 getNodeAnimLength();
    const char* getNodeAnimName();
    const char* getVisAnimName();
    const char* getTexPatAnimName();
    const char* getTexSrtAnimName();
    const char* getClrAnimName();
    bool isNodeAnimFinished();
    bool isVisAnimFinished();
    bool isClrAnimFinished();
    bool isTexPatAnimFinished();
    bool isTexSrtAnimFinished();
    bool isAnimFinished();
    bool isNodeAnimLoop();
    void getPos(Vec3f* pos);
    void getPos(Vec3f* pos, const char* nodeName);
    void setPos(Vec3f* pos);
    void setPos(Vec3f* pos, const char* nodeName);
    void setTrans(Vec3f* trans);
    void getRect3D(Rect2D* rect, const char* nodeNameA, const char* nodeNameB);
    void getRect3D(Rect2D* rect, int nodeA, int nodeB);
    nw4r::g3d::ResNode getNode(const char* nodeName);
    u32 getNodeID(const char* nodeName);
    Matrix getNodeMatrix(const char* nodeName);
    Vec3f getGlobalPosition(int resNode);
    Vec3f getGlobalPosition(const char* nodeName);
    Vec3f getGlobalPosition();
    void getAnimScale(Vec3f* scl, const char* name);
    Vec3f getScale(const char* nodeName);
    void setObjScale(Vec3f* scale);
    Vec3f getObjScale();
    void setRotate(Vec3f* rot);
    void setRotate(const char* nodeName, Vec3f* rot);
    void setObjRotate(Vec3f* rot);
    void getRotate(Vec3f* rot, const char* nodeName);
    void setScale(const char* nodeName, Vec3f* scale);
    void changeMaterialTex(const char* matName, GXTexObj* srcObj);
    void changeMaterialTex(const char* matName, void* image, u16 width, u16 height);
    void changeAnimN(int animId, u32 flags, bool play, bool reset);
    void setFrame(float frame);
    void setFrameNode(float frame);
    void setFrameVisible(float frame);
    void setFrameTex(float frame);
    void setFrameTexSrt(float frame);
    void setFrameMatCol(float frame);
};

MuObject* MuObject::create(nw4r::g3d::ResFile* modelSource, const char* modelNode, int drawPriority, nw4r::g3d::ResFile* textureSource, Heaps::HeapType type) {
    return new (type) MuObject(modelSource, modelNode, drawPriority, textureSource, true, type);
}

MuObject* MuObject::create(nw4r::g3d::ResFile* modelSource, int modelNode, nw4r::g3d::ResFile* textureSource, int animNode, Heaps::HeapType type) {
    return new (type) MuObject(modelSource, animNode, modelNode, textureSource, true, type);
}

MuObject* MuObject::createAlt(nw4r::g3d::ResFile* modelSource, const char* modelNode, int drawPriority, nw4r::g3d::ResFile* textureSource, Heaps::HeapType type) {
    return new (type) MuObject(modelSource, modelNode, drawPriority, textureSource, false, type);
}

// Frame policy used when a binding is replaced: clamp the frame into [start, end - epsilon].
float muObjPlayPolicyOneTime(float frame, float end, float start) {
    float d = start - frame;
    float last = end - 1.0f;
    float v = nw4r::math::FSelect(d, start, frame);
    return nw4r::math::FSelect(v - last, last, v);
}

static inline void setPolicy(void* obj, u32 policy) {
    void* fn;
    if (policy == 0) {
        fn = (void*)muObjPlayPolicyOneTime;
    } else {
        fn = lbl_8059C648[policy];
    }
    *(void**)((u8*)obj + 0x28) = fn;
}

static inline void setChrAnim(nw4r::g3d::ResAnmChr anim, gfModelAnimation* modelAnim, nw4r::g3d::ResMdl model, Heaps::HeapType heap) {
    int instanceSize;
    MEMAllocator* allocator = gfHeapManager::getMEMAllocator(heap);
    if (anim.IsValid()) {
        nw4r::g3d::AnmObjChrRes* anmObj = nw4r::g3d::AnmObjChrRes::Construct(allocator, &instanceSize, anim, model, false);
        if (anmObj != NULL) {
            anmObj->Bind(model);
            if (modelAnim->m_anmObjChrRes != NULL) {
                modelAnim->m_anmObjChrRes->Destroy();
            }
            modelAnim->m_anmObjChrRes = anmObj;
        }
    }
}

static inline void setVisAnim(nw4r::g3d::ResAnmVis anim, gfModelAnimation* modelAnim, nw4r::g3d::ResMdl model, Heaps::HeapType heap) {
    int instanceSize;
    MEMAllocator* allocator = gfHeapManager::getMEMAllocator(heap);
    if (anim.IsValid()) {
        nw4r::g3d::AnmObjVisRes* anmObj = nw4r::g3d::AnmObjVisRes::Construct(allocator, &instanceSize, anim, model);
        if (anmObj != NULL) {
            anmObj->Bind(model);
            if (modelAnim->m_anmObjVisRes != NULL) {
                modelAnim->m_anmObjVisRes->Destroy();
            }
            modelAnim->m_anmObjVisRes = anmObj;
        }
    }
}

static inline void setTexPatAnim(nw4r::g3d::ResAnmTexPat anim, gfModelAnimation* modelAnim, nw4r::g3d::ResMdl model, Heaps::HeapType heap) {
    int instanceSize;
    if (anim.IsValid()) {
        MEMAllocator* allocator = gfHeapManager::getMEMAllocator(heap);
        nw4r::g3d::AnmObjTexPatRes* anmObj = nw4r::g3d::AnmObjTexPatRes::Construct(allocator, &instanceSize, anim, model, false);
        if (anmObj != NULL) {
            anmObj->Bind(model);
            if (modelAnim->m_anmObjTexPatRes != NULL) {
                modelAnim->m_anmObjTexPatRes->Destroy();
            }
            modelAnim->m_anmObjTexPatRes = anmObj;
        }
    }
}

static inline void setTexSrtAnim(nw4r::g3d::ResAnmTexSrt anim, gfModelAnimation* modelAnim, nw4r::g3d::ResMdl model, Heaps::HeapType heap) {
    int instanceSize;
    if (anim.IsValid()) {
        MEMAllocator* allocator = gfHeapManager::getMEMAllocator(heap);
        nw4r::g3d::AnmObjTexSrtRes* anmObj = nw4r::g3d::AnmObjTexSrtRes::Construct(allocator, &instanceSize, anim, model, false);
        if (anmObj != NULL) {
            anmObj->Bind(model);
            if (modelAnim->m_anmObjTexSrtRes != NULL) {
                modelAnim->m_anmObjTexSrtRes->Destroy();
            }
            modelAnim->m_anmObjTexSrtRes = anmObj;
        }
    }
}

static inline void setClrAnim(nw4r::g3d::ResAnmClr anim, gfModelAnimation* modelAnim, nw4r::g3d::ResMdl model, Heaps::HeapType heap) {
    int instanceSize;
    if (anim.IsValid()) {
        MEMAllocator* allocator = gfHeapManager::getMEMAllocator(heap);
        nw4r::g3d::AnmObjMatClrRes* anmObj = nw4r::g3d::AnmObjMatClrRes::Construct(allocator, &instanceSize, anim, model, false);
        if (anmObj != NULL) {
            anmObj->Bind(model);
            if (modelAnim->m_anmObjMatClrRes != NULL) {
                modelAnim->m_anmObjMatClrRes->Destroy();
            }
            modelAnim->m_anmObjMatClrRes = anmObj;
        }
    }
}

static inline void setTexPatAnimIdx(u32 animId, nw4r::g3d::ResMdl model, Heaps::HeapType heap, gfModelAnimation* modelAnim) {
    if (animId < modelAnim->m_resFile.GetResAnmTexPatNumEntries()) {
        int instanceSize;
        nw4r::g3d::AnmObjTexPatRes* anmObj;
        nw4r::g3d::ResAnmTexPat anim = modelAnim->m_resFile.GetResAnmTexPat(animId);
        if (anim.IsValid()) {
            MEMAllocator* allocator = gfHeapManager::getMEMAllocator(heap);
            anmObj = nw4r::g3d::AnmObjTexPatRes::Construct(allocator, &instanceSize, anim, model, false);
            if (anmObj != NULL) {
                anmObj->Bind(model);
                if (modelAnim->m_anmObjTexPatRes != NULL) {
                    modelAnim->m_anmObjTexPatRes->Destroy();
                }
                modelAnim->m_anmObjTexPatRes = anmObj;
            }
        }
    }
}

static inline void bindNodeAnimImpl(MuObject* self, nw4r::g3d::ResAnmChr anim) {
    self->m_modelAnim->unbindNodeAnim(self->m_sceneModel);
    setChrAnim(anim, self->m_modelAnim, self->m_resMdl, self->m_heapType);
    self->m_modelAnim->bindNodeAnim(self->m_sceneModel);
    nw4r::g3d::AnmObjChrRes* o = self->m_modelAnim->m_anmObjChrRes;
    setPolicy(o, *(u32*)((u8*)o->m_anmChrFile.ptr() + 0x20));
    nw4r::g3d::ScnMdl* sceneModel = self->m_sceneModel;
    sceneModel->SetScnObjOption(2, 0);
    sceneModel->SetScnObjOption(5, 0);
}

void MuObject::changeNodeAnimN(const char* animName) {
    nw4r::g3d::ResAnmChr anim = ResFile_GetResAnmChrByName(&m_resFile, animName);
    if (anim.IsValid()) {
        bindNodeAnimImpl(this, anim);
    }
}

bool MuObject::changeNodeAnimNIf(const char* animName) {
    nw4r::g3d::ResAnmChr anim = ResFile_GetResAnmChrByName(&m_resFile, animName);
    if (!anim.IsValid()) {
        return false;
    }
    m_modelAnim->unbindNodeAnim(m_sceneModel);
    setChrAnim(anim, m_modelAnim, m_resMdl, m_heapType);
    m_modelAnim->bindNodeAnim(m_sceneModel);
    nw4r::g3d::AnmObjChrRes* o = m_modelAnim->m_anmObjChrRes;
    setPolicy(o, *(u32*)((u8*)o->m_anmChrFile.ptr() + 0x20));
    nw4r::g3d::ScnMdl* sceneModel = m_sceneModel;
    sceneModel->SetScnObjOption(2, 0);
    sceneModel->SetScnObjOption(5, 0);
    return true;
}

static inline void bindVisAnimImpl(MuObject* self, nw4r::g3d::ResAnmVis anim) {
    self->m_modelAnim->unbindVisibleAnim(self->m_sceneModel);
    setVisAnim(anim, self->m_modelAnim, self->m_resMdl, self->m_heapType);
    self->m_modelAnim->bindVisibleAnim(self->m_sceneModel);
    nw4r::g3d::AnmObjVisRes* o = self->m_modelAnim->m_anmObjVisRes;
    setPolicy(o, *(u32*)((u8*)o->m_anmVisFile.ptr() + 0x20));
    nw4r::g3d::ScnMdl* sceneModel = self->m_sceneModel;
    sceneModel->SetScnObjOption(2, 0);
    sceneModel->SetScnObjOption(5, 0);
}

void MuObject::changeVisAnimN(const char* animName) {
    nw4r::g3d::ResAnmVis anim = ResFile_GetResAnmVisByName(&m_resFile, animName);
    if (anim.IsValid()) {
        bindVisAnimImpl(this, anim);
    }
}

bool MuObject::changeVisAnimNIf(const char* animName) {
    nw4r::g3d::ResAnmVis anim = ResFile_GetResAnmVisByName(&m_resFile, animName);
    if (!anim.IsValid()) {
        return false;
    }
    m_modelAnim->unbindVisibleAnim(m_sceneModel);
    setVisAnim(anim, m_modelAnim, m_resMdl, m_heapType);
    m_modelAnim->bindVisibleAnim(m_sceneModel);
    nw4r::g3d::AnmObjVisRes* o = m_modelAnim->m_anmObjVisRes;
    setPolicy(o, *(u32*)((u8*)o->m_anmVisFile.ptr() + 0x20));
    nw4r::g3d::ScnMdl* sceneModel = m_sceneModel;
    sceneModel->SetScnObjOption(2, 0);
    sceneModel->SetScnObjOption(5, 0);
    return true;
}

static inline void bindTexPatAnimIdxImpl(MuObject* self, u32 index) {
    self->m_modelAnim->unbindTexAnim(self->m_sceneModel);
    setTexPatAnimIdx(index, self->m_resMdl, self->m_heapType, self->m_modelAnim);
    self->m_modelAnim->bindTexAnim(self->m_sceneModel);
    nw4r::g3d::AnmObjTexPatRes* o = self->m_modelAnim->m_anmObjTexPatRes;
    setPolicy(o, *(u32*)((u8*)o->m_anmTexPatFile.ptr() + 0x34));
    self->m_sceneModel->SetScnObjOption(3, 0);
}

void MuObject::changeTexPatAnim(u32 index) {
    if (index < m_resFile.GetResAnmTexPatNumEntries()) {
        bindTexPatAnimIdxImpl(this, index);
    }
}

static inline void bindTexPatAnimImpl(MuObject* self, nw4r::g3d::ResAnmTexPat anim) {
    self->m_modelAnim->unbindTexAnim(self->m_sceneModel);
    setTexPatAnim(anim, self->m_modelAnim, self->m_resMdl, self->m_heapType);
    self->m_modelAnim->bindTexAnim(self->m_sceneModel);
    nw4r::g3d::AnmObjTexPatRes* o = self->m_modelAnim->m_anmObjTexPatRes;
    setPolicy(o, *(u32*)((u8*)o->m_anmTexPatFile.ptr() + 0x34));
    self->m_sceneModel->SetScnObjOption(3, 0);
}

void MuObject::changeTexPatAnimN(const char* animName) {
    nw4r::g3d::ResAnmTexPat anim = ResFile_GetResAnmTexPatByName(&m_resFile, animName);
    if (anim.IsValid()) {
        bindTexPatAnimImpl(this, anim);
    }
}

bool MuObject::changeTexPatAnimNIf(const char* animName) {
    nw4r::g3d::ResAnmTexPat anim = ResFile_GetResAnmTexPatByName(&m_resFile, animName);
    if (!anim.IsValid()) {
        return false;
    }
    m_modelAnim->unbindTexAnim(m_sceneModel);
    setTexPatAnim(anim, m_modelAnim, m_resMdl, m_heapType);
    m_modelAnim->bindTexAnim(m_sceneModel);
    nw4r::g3d::AnmObjTexPatRes* o = m_modelAnim->m_anmObjTexPatRes;
    setPolicy(o, *(u32*)((u8*)o->m_anmTexPatFile.ptr() + 0x34));
    m_sceneModel->SetScnObjOption(3, 0);
    return true;
}

static inline void bindTexSrtAnimImpl(MuObject* self, nw4r::g3d::ResAnmTexSrt anim) {
    self->m_modelAnim->unbindTexSrtAnim(self->m_sceneModel);
    setTexSrtAnim(anim, self->m_modelAnim, self->m_resMdl, self->m_heapType);
    self->m_modelAnim->bindTexSrtAnim(self->m_sceneModel);
    nw4r::g3d::AnmObjTexSrtRes* o = self->m_modelAnim->m_anmObjTexSrtRes;
    setPolicy(o, *(u32*)((u8*)o->m_anmTexSrtFile.ptr() + 0x24));
    self->m_sceneModel->SetScnObjOption(3, 0);
}

void MuObject::changeTexSrtAnimN(const char* animName) {
    nw4r::g3d::ResAnmTexSrt anim = ResFile_GetResAnmTexSrtByName(&m_resFile, animName);
    if (anim.IsValid()) {
        bindTexSrtAnimImpl(this, anim);
    }
}

bool MuObject::changeTexSrtAnimNIf(const char* animName) {
    nw4r::g3d::ResAnmTexSrt anim = ResFile_GetResAnmTexSrtByName(&m_resFile, animName);
    if (!anim.IsValid()) {
        return false;
    }
    m_modelAnim->unbindTexSrtAnim(m_sceneModel);
    setTexSrtAnim(anim, m_modelAnim, m_resMdl, m_heapType);
    m_modelAnim->bindTexSrtAnim(m_sceneModel);
    nw4r::g3d::AnmObjTexSrtRes* o = m_modelAnim->m_anmObjTexSrtRes;
    setPolicy(o, *(u32*)((u8*)o->m_anmTexSrtFile.ptr() + 0x24));
    m_sceneModel->SetScnObjOption(3, 0);
    return true;
}

static inline void bindClrAnimImpl(MuObject* self, nw4r::g3d::ResAnmClr anim) {
    self->m_modelAnim->unbindMatColAnim(self->m_sceneModel);
    setClrAnim(anim, self->m_modelAnim, self->m_resMdl, self->m_heapType);
    self->m_modelAnim->bindMatColAnim(self->m_sceneModel);
    nw4r::g3d::AnmObjMatClrRes* o = self->m_modelAnim->m_anmObjMatClrRes;
    setPolicy(o, *(u32*)((u8*)o->m_anmMatClrFile.ptr() + 0x20));
    self->m_sceneModel->SetScnObjOption(3, 0);
}

void MuObject::changeClrAnimN(const char* animName) {
    nw4r::g3d::ResAnmClr anim = ResFile_GetResAnmClrByName(&m_resFile, animName);
    if (anim.IsValid()) {
        bindClrAnimImpl(this, anim);
    }
}

bool MuObject::changeClrAnimNIf(const char* animName) {
    nw4r::g3d::ResAnmClr anim = ResFile_GetResAnmClrByName(&m_resFile, animName);
    if (!anim.IsValid()) {
        return false;
    }
    m_modelAnim->unbindMatColAnim(m_sceneModel);
    setClrAnim(anim, m_modelAnim, m_resMdl, m_heapType);
    m_modelAnim->bindMatColAnim(m_sceneModel);
    nw4r::g3d::AnmObjMatClrRes* o = m_modelAnim->m_anmObjMatClrRes;
    setPolicy(o, *(u32*)((u8*)o->m_anmMatClrFile.ptr() + 0x20));
    m_sceneModel->SetScnObjOption(3, 0);
    return true;
}

u16 MuObject::getNodeAnimLength() {
    nw4r::g3d::AnmObjChrRes* o = m_modelAnim->m_anmObjChrRes;
    if (o == NULL) {
        return 0;
    }
    return o->m_anmChrFile.ptr()->m_animLength;
}

void MuObject::changeAnimN(const char* animName) {
    {
        nw4r::g3d::ResAnmChr anim = ResFile_GetResAnmChrByName(&m_resFile, animName);
        if (anim.IsValid()) {
            bindNodeAnimImpl(this, anim);
        }
    }
    {
        nw4r::g3d::ResAnmVis anim = ResFile_GetResAnmVisByName(&m_resFile, animName);
        if (anim.IsValid()) {
            bindVisAnimImpl(this, anim);
        }
    }
    {
        nw4r::g3d::ResAnmTexPat anim = ResFile_GetResAnmTexPatByName(&m_resFile, animName);
        if (anim.IsValid()) {
            bindTexPatAnimImpl(this, anim);
        }
    }
    {
        nw4r::g3d::ResAnmTexSrt anim = ResFile_GetResAnmTexSrtByName(&m_resFile, animName);
        if (anim.IsValid()) {
            bindTexSrtAnimImpl(this, anim);
        }
    }
    {
        nw4r::g3d::ResAnmClr anim = ResFile_GetResAnmClrByName(&m_resFile, animName);
        if (anim.IsValid()) {
            bindClrAnimImpl(this, anim);
        }
    }
}

const char* MuObject::getNodeAnimName() {
    nw4r::g3d::AnmObjChrRes* o = m_modelAnim->m_anmObjChrRes;
    if (o == NULL) {
        return NULL;
    }
    u8* d = (u8*)o->m_anmChrFile.ptr();
    u32 offset = *(u32*)(d + 0x14);
    if (offset != 0) {
        return (const char*)(d + offset);
    }
    return NULL;
}

const char* MuObject::getVisAnimName() {
    nw4r::g3d::AnmObjVisRes* o = m_modelAnim->m_anmObjVisRes;
    if (o == NULL) {
        return NULL;
    }
    u8* d = (u8*)o->m_anmVisFile.ptr();
    u32 offset = *(u32*)(d + 0x14);
    if (offset != 0) {
        return (const char*)(d + offset);
    }
    return NULL;
}

const char* MuObject::getTexPatAnimName() {
    nw4r::g3d::AnmObjTexPatRes* o = m_modelAnim->m_anmObjTexPatRes;
    if (o == NULL) {
        return NULL;
    }
    u8* d = (u8*)o->m_anmTexPatFile.ptr();
    u32 offset = *(u32*)(d + 0x24);
    if (offset != 0) {
        return (const char*)(d + offset);
    }
    return NULL;
}

const char* MuObject::getTexSrtAnimName() {
    nw4r::g3d::AnmObjTexSrtRes* o = m_modelAnim->m_anmObjTexSrtRes;
    if (o == NULL) {
        return NULL;
    }
    u8* d = (u8*)o->m_anmTexSrtFile.ptr();
    u32 offset = *(u32*)(d + 0x14);
    if (offset != 0) {
        return (const char*)(d + offset);
    }
    return NULL;
}

const char* MuObject::getClrAnimName() {
    nw4r::g3d::AnmObjMatClrRes* o = m_modelAnim->m_anmObjMatClrRes;
    if (o == NULL) {
        return NULL;
    }
    u8* d = (u8*)o->m_anmMatClrFile.ptr();
    u32 offset = *(u32*)(d + 0x14);
    if (offset != 0) {
        return (const char*)(d + offset);
    }
    return NULL;
}

bool MuObject::isNodeAnimFinished() {
    if (m_modelAnim == NULL) {
        return true;
    }
    nw4r::g3d::AnmObjChrRes* o = m_modelAnim->m_anmObjChrRes;
    if (o == NULL) {
        return true;
    }
    u8* d = (u8*)o->m_anmChrFile.ptr();
    if (*(int*)(d + 0x20) != 1) {
        u16 length = *(u16*)(d + 0x1c);
        if (o->GetFrame() >= (float)(length - 1)) {
            return true;
        }
    }
    return false;
}

bool MuObject::isVisAnimFinished() {
    if (m_modelAnim == NULL) {
        return true;
    }
    nw4r::g3d::AnmObjVisRes* o = m_modelAnim->m_anmObjVisRes;
    if (o == NULL) {
        return true;
    }
    u8* d = (u8*)o->m_anmVisFile.ptr();
    if (*(int*)(d + 0x20) != 1) {
        u16 length = *(u16*)(d + 0x1c);
        if (o->GetFrame() >= (float)(length - 1)) {
            return true;
        }
    }
    return false;
}

bool MuObject::isClrAnimFinished() {
    if (m_modelAnim == NULL) {
        return true;
    }
    nw4r::g3d::AnmObjMatClrRes* o = m_modelAnim->m_anmObjMatClrRes;
    if (o == NULL) {
        return true;
    }
    u8* d = (u8*)o->m_anmMatClrFile.ptr();
    if (*(int*)(d + 0x20) != 1) {
        u16 length = *(u16*)(d + 0x1c);
        if (o->GetFrame() >= (float)(length - 1)) {
            return true;
        }
    }
    return false;
}

inline bool MuObject::isTexPatAnimFinished() {
    if (m_modelAnim == NULL) {
        return true;
    }
    nw4r::g3d::AnmObjTexPatRes* o = m_modelAnim->m_anmObjTexPatRes;
    if (o == NULL) {
        return true;
    }
    u8* d = (u8*)o->m_anmTexPatFile.ptr();
    if (*(int*)(d + 0x34) != 1) {
        u16 length = *(u16*)(d + 0x2c);
        if (o->GetFrame() >= (float)(length - 1)) {
            return true;
        }
    }
    return false;
}

inline bool MuObject::isTexSrtAnimFinished() {
    if (m_modelAnim == NULL) {
        return true;
    }
    nw4r::g3d::AnmObjTexSrtRes* o = m_modelAnim->m_anmObjTexSrtRes;
    if (o == NULL) {
        return true;
    }
    u8* d = (u8*)o->m_anmTexSrtFile.ptr();
    if (*(int*)(d + 0x24) != 1) {
        u16 length = *(u16*)(d + 0x1c);
        if (o->GetFrame() >= (float)(length - 1)) {
            return true;
        }
    }
    return false;
}

bool MuObject::isAnimFinished() {
    if (!isNodeAnimFinished()) {
        return false;
    }
    if (!isVisAnimFinished()) {
        return false;
    }
    if (!isTexPatAnimFinished()) {
        return false;
    }
    if (!isTexSrtAnimFinished()) {
        return false;
    }
    return isClrAnimFinished();
}

bool MuObject::isNodeAnimLoop() {
    nw4r::g3d::AnmObjChrRes* o = m_modelAnim->m_anmObjChrRes;
    if (o == NULL) {
        return false;
    }
    return *(u32*)((u8*)o->m_anmChrFile.ptr() + 0x20) == 1;
}

void MuObject::getPos(Vec3f* pos) {
    nw4r::g3d::ResMdl mdl = m_sceneModel->m_resMdl;
    nw4r::g3d::ResNode node = mdl.GetResNode(m_baseNode);
    pos->m_x = node->m_translation.m_x;
    pos->m_y = node->m_translation.m_y;
    pos->m_z = node->m_translation.m_z;
}

void MuObject::getPos(Vec3f* pos, const char* nodeName) {
    nw4r::g3d::ResMdl mdl = m_sceneModel->m_resMdl;
    nw4r::g3d::ResNode node = mdl.GetResNode(nodeName);
    pos->m_x = node->m_translation.m_x;
    pos->m_y = node->m_translation.m_y;
    pos->m_z = node->m_translation.m_z;
}

void MuObject::setPos(Vec3f* pos) {
    nw4r::g3d::ResMdl mdl = m_sceneModel->m_resMdl;
    nw4r::g3d::ResNode node = mdl.GetResNode(m_baseNode);
    node.SetTranslate(pos->m_x, pos->m_y, pos->m_z);
}

void MuObject::setPos(Vec3f* pos, const char* nodeName) {
    nw4r::g3d::ResMdl mdl = m_sceneModel->m_resMdl;
    nw4r::g3d::ResNode node = mdl.GetResNode(nodeName);
    node.SetTranslate(pos->m_x, pos->m_y, pos->m_z);
}

void MuObject::setTrans(Vec3f* trans) {
    m_trans = *trans;
    Vec3f scale(1.0f, 1.0f, 1.0f);
    Matrix mtx;
    mtx.setSRT(scale, m_rot, m_trans);
    ScnMdl_SetNodeMtx(m_scnMdl, 0, &mtx);
    nw4r::g3d::ScnMdl* sceneModel = m_sceneModel;
    sceneModel->SetScnObjOption(2, 0);
    sceneModel->SetScnObjOption(5, 0);
}

void MuObject::getRect3D(Rect2D* rect, const char* nodeNameA, const char* nodeNameB) {
    nw4r::g3d::ResMdl mdl = m_sceneModel->m_resMdl;
    nw4r::g3d::ResNode nodeA = mdl.GetResNode(nodeNameA);
    nw4r::g3d::ResNode nodeB = mdl.GetResNode(nodeNameB);
    u32 idB = nodeB.IsValid() ? nodeB->m_nodeIndex : 0;
    Vec3f a;
    a = nwSMGetGlobalPosition(m_sceneModel, nodeA.IsValid() ? nodeA->m_nodeIndex : 0);
    Vec3f b;
    b = nwSMGetGlobalPosition(m_sceneModel, idB);
    rect->m_left = nw4r::math::FSelect(a.m_x - b.m_x, b.m_x, a.m_x);
    rect->m_right = nw4r::math::FSelect(a.m_x - b.m_x, a.m_x, b.m_x);
    rect->m_up = nw4r::math::FSelect(b.m_y - a.m_y, b.m_y, a.m_y);
    rect->m_down = nw4r::math::FSelect(b.m_y - a.m_y, a.m_y, b.m_y);
}

void MuObject::getRect3D(Rect2D* rect, int nodeA, int nodeB) {
    Vec3f a;
    a = nwSMGetGlobalPosition(m_sceneModel, nodeA);
    Vec3f b;
    b = nwSMGetGlobalPosition(m_sceneModel, nodeB);
    rect->m_left = nw4r::math::FSelect(a.m_x - b.m_x, b.m_x, a.m_x);
    rect->m_right = nw4r::math::FSelect(a.m_x - b.m_x, a.m_x, b.m_x);
    rect->m_up = nw4r::math::FSelect(b.m_y - a.m_y, b.m_y, a.m_y);
    rect->m_down = nw4r::math::FSelect(b.m_y - a.m_y, a.m_y, b.m_y);
}

nw4r::g3d::ResNode MuObject::getNode(const char* nodeName) {
    nw4r::g3d::ResMdl mdl = m_sceneModel->m_resMdl;
    return mdl.GetResNode(nodeName);
}

u32 MuObject::getNodeID(const char* nodeName) {
    nw4r::g3d::ResMdl mdl = m_sceneModel->m_resMdl;
    nw4r::g3d::ResNode node = mdl.GetResNode(nodeName);
    return node.IsValid() ? node->m_nodeIndex : 0;
}

Matrix MuObject::getNodeMatrix(const char* nodeName) {
    nw4r::g3d::ResMdl mdl = m_sceneModel->m_resMdl;
    nw4r::g3d::ResNode node = mdl.GetResNode(nodeName);
    Vec3f trans(node->m_translation.m_x, node->m_translation.m_y, node->m_translation.m_z);
    Vec3f rot(node->m_rotation.m_x, node->m_rotation.m_y, node->m_rotation.m_z);
    Vec3f scale(node->m_scale.m_x, node->m_scale.m_y, node->m_scale.m_z);
    Matrix mtx(true);
    mtx.setSRT(scale, rot, trans);
    return mtx;
}

Vec3f MuObject::getGlobalPosition(int resNode) {
    return nwSMGetGlobalPosition(m_sceneModel, resNode);
}

Vec3f MuObject::getGlobalPosition(const char* nodeName) {
    nw4r::g3d::ResMdl mdl = m_sceneModel->m_resMdl;
    nw4r::g3d::ResNode node = mdl.GetResNode(nodeName);
    return nwSMGetGlobalPosition(m_sceneModel, node.IsValid() ? node->m_nodeIndex : 0);
}

Vec3f MuObject::getGlobalPosition() {
    nw4r::g3d::ResMdl mdl = m_sceneModel->m_resMdl;
    nw4r::g3d::ResNode node = mdl.GetResNode(m_baseNode);
    return nwSMGetGlobalPosition(m_sceneModel, node.IsValid() ? node->m_nodeIndex : 0);
}

void MuObject::getAnimScale(Vec3f* scl, const char* name) {
    nw4r::g3d::ResMdl mdl = m_sceneModel->m_resMdl;
    nw4r::g3d::ResNode node = mdl.GetResNode(name);
    scl->m_x = node->m_scale.m_x;
    scl->m_y = node->m_scale.m_y;
    scl->m_z = node->m_scale.m_z;
}

Vec3f MuObject::getScale(const char* nodeName) {
    nw4r::g3d::ResMdl mdl = m_sceneModel->m_resMdl;
    nw4r::g3d::ResNode node = mdl.GetResNode(nodeName);
    u32 id = node.IsValid() ? node->m_nodeIndex : 0;
    ChrAnmResult res;
    m_modelAnim->m_anmObjChrRes->GetResult((int*)&res, id);
    Vec3f scale;
    ChrAnmResult_GetScale(&res, &scale);
    Vec3f ret;
    ret = scale;
    return ret;
}

static inline void ScnObj_SetScale(nw4r::g3d::ScnMdl* mdl, const Vec3f& v) {
    Vec3f* dst = (Vec3f*)((u8*)mdl + 0xdc);
    float x = v.m_x;
    float y = v.m_y;
    dst->m_x = x;
    dst->m_y = y;
    dst->m_z = v.m_z;
}

void MuObject::setObjScale(Vec3f* scale) {
    ScnObj_SetScale(m_sceneModel, *scale);
    nw4r::g3d::ScnMdl* sceneModel = m_sceneModel;
    sceneModel->SetScnObjOption(2, 0);
    sceneModel->SetScnObjOption(5, 0);
}

static inline Vec3f ScnObj_GetScale(nw4r::g3d::ScnMdl* mdl) {
    Vec3f* src = (Vec3f*)((u8*)mdl + 0xdc);
    Vec3f r;
    r = *src;
    return r;
}

Vec3f MuObject::getObjScale() {
    return ScnObj_GetScale(m_sceneModel);
}

void MuObject::setRotate(Vec3f* rot) {
    nw4r::g3d::ResMdl mdl = m_sceneModel->m_resMdl;
    nw4r::g3d::ResNode node = mdl.GetResNode(m_baseNode);
    ResNode_SetRotate(&node, rot->m_x, rot->m_y, rot->m_z);
}

void MuObject::setRotate(const char* nodeName, Vec3f* rot) {
    nw4r::g3d::ResMdl mdl = m_sceneModel->m_resMdl;
    nw4r::g3d::ResNode node = mdl.GetResNode(nodeName);
    ResNode_SetRotate(&node, rot->m_x, rot->m_y, rot->m_z);
}

void MuObject::setObjRotate(Vec3f* rot) {
    m_rot = *rot;
    Vec3f scale(1.0f, 1.0f, 1.0f);
    Matrix mtx;
    mtx.setSRT(scale, m_rot, m_trans);
    ScnMdl_SetNodeMtx(m_scnMdl, 0, &mtx);
    nw4r::g3d::ScnMdl* sceneModel = m_sceneModel;
    sceneModel->SetScnObjOption(2, 0);
    sceneModel->SetScnObjOption(5, 0);
}

void MuObject::getRotate(Vec3f* rot, const char* nodeName) {
    nw4r::g3d::ResMdl mdl = m_sceneModel->m_resMdl;
    nw4r::g3d::ResNode node = mdl.GetResNode(nodeName);
    rot->m_x = node->m_rotation.m_x;
    rot->m_y = node->m_rotation.m_y;
    rot->m_z = node->m_rotation.m_z;
}

void MuObject::setScale(const char* nodeName, Vec3f* scale) {
    nw4r::g3d::ResMdl mdl = m_sceneModel->m_resMdl;
    nw4r::g3d::ResNode node = mdl.GetResNode(nodeName);
    ResNode_SetScale(&node, scale->m_x, scale->m_y, scale->m_z);
}

void MuObject::setFrameNode(float frame) {
    if (frame != m_modelAnim->m_anmObjChrRes->GetFrame()) {
        nw4r::g3d::ScnMdl* sceneModel = m_sceneModel;
        sceneModel->SetScnObjOption(2, 0);
        sceneModel->SetScnObjOption(5, 0);
    }
    m_modelAnim->m_anmObjChrRes->SetFrame(frame);
}

void MuObject::setFrameVisible(float frame) {
    if (frame != m_modelAnim->m_anmObjVisRes->GetFrame()) {
        nw4r::g3d::ScnMdl* sceneModel = m_sceneModel;
        sceneModel->SetScnObjOption(2, 0);
        sceneModel->SetScnObjOption(5, 0);
    }
    m_modelAnim->m_anmObjVisRes->SetFrame(frame);
}

void MuObject::setFrameTex(float frame) {
    if (frame != m_modelAnim->m_anmObjTexPatRes->GetFrame()) {
        m_sceneModel->SetScnObjOption(3, 0);
    }
    m_modelAnim->m_anmObjTexPatRes->SetFrame(frame);
}

void MuObject::setFrameTexSrt(float frame) {
    if (frame != m_modelAnim->m_anmObjTexSrtRes->GetFrame()) {
        m_sceneModel->SetScnObjOption(3, 0);
    }
    m_modelAnim->m_anmObjTexSrtRes->SetFrame(frame);
}

void MuObject::setFrameMatCol(float frame) {
    if (frame != m_modelAnim->m_anmObjMatClrRes->GetFrame()) {
        m_sceneModel->SetScnObjOption(3, 0);
    }
    m_modelAnim->m_anmObjMatClrRes->SetFrame(frame);
}

void MuObject::changeMaterialTex(const char* matName, GXTexObj* srcObj) {
    u32 matId = m_resMdl.GetResMat(matName)->m_id;
    MatAccess access(m_scnMdl, matId);
    void* image;
    GXTexFmt fmt;
    GXTexWrapMode wrapS;
    GXTexWrapMode wrapT;
    nw4r::g3d::ResTexObj texObj(CopiedMatAccess_GetResTexObj(&access, false));
    u16 width;
    u16 height;
    GXBool mipmap;
    GXTexObj* obj = texObj.GetTexObj(GX_TEXMAP0);
    GXGetTexObjAll(srcObj, &image, &width, &height, &fmt, &wrapS, &wrapT, &mipmap);
    GXInitTexObj(obj, image, width, height, fmt, wrapS, wrapT, mipmap);
}

void MuObject::changeMaterialTex(const char* matName, void* image, u16 width, u16 height) {
    nw4r::g3d::ResTexObj texObj(NULL);
    u32 matId = m_resMdl.GetResMat(matName)->m_id;
    MatAccess access(m_scnMdl, matId);
    texObj = nw4r::g3d::ResTexObj(CopiedMatAccess_GetResTexObj(&access, false));
    GXTexObj* obj = texObj.GetTexObj(GX_TEXMAP0);
    GXInitTexObj(obj, image, width, height, GX_TF_RGBA8, GX_CLAMP, GX_CLAMP, false);
    GXLoadTexObj(obj, GX_TEXMAP0);
}

void MuObject::setFrame(float frame) {
    if (m_modelAnim->m_anmObjChrRes != NULL) {
        setFrameNode(frame);
    }
    if (m_modelAnim->m_anmObjVisRes != NULL) {
        setFrameVisible(frame);
    }
    if (m_modelAnim->m_anmObjTexPatRes != NULL) {
        setFrameTex(frame);
    }
    if (m_modelAnim->m_anmObjTexSrtRes != NULL) {
        setFrameTexSrt(frame);
    }
    if (m_modelAnim->m_anmObjMatClrRes != NULL) {
        setFrameMatCol(frame);
    }
}

static inline const char* ResMdl_GetName(nw4r::g3d::ResMdl& mdl) {
    u8* data = (u8*)mdl.ptr();
    u32 off = *(u32*)(data + 0x3c);
    return off != 0 ? (const char*)(data + off) : NULL;
}

void MuObject::changeAnimN(int animId, u32 flags, bool play, bool reset) {
    char name[0x40];
    sprintf(name, lbl_8059DF20, ResMdl_GetName(m_resMdl), animId);
    float rate = play ? 1.0f : 0.0f;
    if (flags & 1) {
        changeNodeAnimN(name);
        m_modelAnim->m_anmObjChrRes->SetUpdateRate(rate);
        if (reset) {
            setFrameNode(0.0f);
        }
    }
    if (flags & 2) {
        changeVisAnimN(name);
        m_modelAnim->m_anmObjVisRes->SetUpdateRate(rate);
        if (reset) {
            setFrameVisible(0.0f);
        }
    }
    if (flags & 4) {
        changeTexPatAnimN(name);
        m_modelAnim->m_anmObjTexPatRes->SetUpdateRate(rate);
        if (reset) {
            setFrameTex(0.0f);
        }
    }
    if (flags & 8) {
        changeTexSrtAnimN(name);
        m_modelAnim->m_anmObjTexSrtRes->SetUpdateRate(rate);
        if (reset) {
            setFrameTexSrt(0.0f);
        }
    }
    if (flags & 0x10) {
        changeClrAnimN(name);
        m_modelAnim->m_anmObjMatClrRes->SetUpdateRate(rate);
        if (reset) {
            setFrameMatCol(0.0f);
        }
    }
}
