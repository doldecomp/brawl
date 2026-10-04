#include <gf/gf_heap_manager.h>
#include <gf/gf_model.h>
#include <nw4r/g3d/g3d_resfile.h>
#include <nw4r/g3d/g3d_resmdl.h>
#include <nw4r/g3d/g3d_scnmdl.h>
#include <nw4r/math/math_arithmetic.h>
#include <sr/sr_common.h>
#include <types.h>

// Animation frame policy function table (lives in gf_model_animation.cpp).
extern void* lbl_8059C648[2];

// ResFile name lookups that are not declared in the BrawlHeaders ResFile class.
nw4r::g3d::ResAnmChr ResFile_GetResAnmChrByName(nw4r::g3d::ResFile* file, const char* name);
nw4r::g3d::ResAnmVis ResFile_GetResAnmVisByName(nw4r::g3d::ResFile* file, const char* name);
nw4r::g3d::ResAnmClr ResFile_GetResAnmClrByName(nw4r::g3d::ResFile* file, const char* name);
nw4r::g3d::ResAnmTexPat ResFile_GetResAnmTexPatByName(nw4r::g3d::ResFile* file, const char* name);
nw4r::g3d::ResAnmTexSrt ResFile_GetResAnmTexSrtByName(nw4r::g3d::ResFile* file, const char* name);

class MuObject {
public:
    virtual ~MuObject();
    nw4r::g3d::ResFile m_resFile;    // 0x04
    nw4r::g3d::ResMdl m_resMdl;      // 0x08
    nw4r::g3d::ScnMdl* m_scnMdl;     // 0x0c
    nw4r::g3d::ScnMdl* m_sceneModel; // 0x10
    gfModelAnimation* m_modelAnim;   // 0x14
    u8 m_18[0x3c];                   // 0x18
    Heaps::HeapType m_heapType;      // 0x54
    u8 m_58[8];                      // 0x58

    MuObject(nw4r::g3d::ResFile* modelSource, const char* modelNode, int drawPriority, nw4r::g3d::ResFile* textureSource, bool isByName, Heaps::HeapType heapType);
    MuObject(nw4r::g3d::ResFile* modelSource, int animNode, int modelNode, nw4r::g3d::ResFile* textureSource, bool isByIndex, Heaps::HeapType heapType);

    static MuObject* create(nw4r::g3d::ResFile* modelSource, const char* modelNode, int drawPriority, nw4r::g3d::ResFile* textureSource, Heaps::HeapType type);
    static MuObject* create(nw4r::g3d::ResFile* modelSource, int modelNode, nw4r::g3d::ResFile* textureSource, int animNode, Heaps::HeapType type);

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
