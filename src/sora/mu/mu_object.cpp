#include <gf/gf_heap_manager.h>
#include <gf/gf_file_io_handle.h>
#include <gf/gf_model.h>
#include <nw4r/g3d/g3d_obj.h>
#include <nw4r/g3d/g3d_resfile.h>
#include <nw4r/g3d/g3d_resmdl.h>
#include <nw4r/g3d/g3d_scnmdl.h>
#include <mt/mt_matrix.h>
#include <mt/mt_vector.h>
#include <nw4r/math/math_arithmetic.h>
#include <ut/ut_nw.h>
#include <sr/sr_common.h>
#include <types.h>
#include <string.h>

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

extern "C" {
void fn_801B0A28();
gfModelAnimation* __ct__16gfModelAnimationFd(void* self, nw4r::g3d::ResFile* file, nw4r::g3d::ResMdl* mdl, bool doBind, int animIndex, Heaps::HeapType heap);
gfModelAnimation* __ct1__16gfModelAnimationFd(void* self, nw4r::g3d::ResFile* file, nw4r::g3d::ResMdl* mdl, bool doBind, const char* animName, Heaps::HeapType heap);
}
void ResFile_Bind(nw4r::g3d::ResFile* self, nw4r::g3d::ResFile file);
nw4r::g3d::ResMdl ResFile_GetResMdlByName(nw4r::g3d::ResFile* file, const char* name);
nw4r::g3d::ResMdl ResFile_GetResMdlByIndex(nw4r::g3d::ResFile* file, int index);
nw4r::g3d::ScnMdl* ScnMdl_Construct(MEMAllocator* allocator, u32* size, nw4r::g3d::ResMdl mdl, u32 bufferOption, int nView, void (*callback)());

extern "C" {
bool fn_80192B00(nw4r::g3d::ResTex* tex, void** image, u16* w, u16* h, GXTexFmt* fmt, f32* minLod, f32* maxLod, GXBool* mipmap);
bool fn_80192A44(nw4r::g3d::ResTex* tex, void** image, u16* w, u16* h, GXTexFmt* fmt, f32* minLod, f32* maxLod, GXBool* mipmap);
void* fn_801AFF94(nw4r::g3d::ScnMdl::CopiedMatAccess* access, bool sync);
GXTlutObj* fn_80190DC8(void** tlutObj, int id);
}

struct ResPlttRef {
    u8* m_data;
};
extern "C" u8* fn_8018D310(nw4r::g3d::ResFile* file, const char* name);

void ScnMdl_SetNodeMtx(nw4r::g3d::ScnMdl* mdl, u32 nodeId, const Matrix* mtx);

struct MuAnimIdxData {
    float m_frame;      // 0x00
    u8 m_04[8];         // 0x04
    u32 m_index;        // 0x0c
    u8 m_flags;         // 0x10
};

struct MuAnimNameData {
    float m_frame;      // 0x00
    u8 m_04[8];         // 0x04
    const char* m_name; // 0x0c
    u8 m_flags;         // 0x10
};

struct ZeroWord {
    u32 m_word;
    ZeroWord() { m_word = 0; }
};

class MuObjProcessTask {
public:
    virtual ~MuObjProcessTask();
};

struct MuObjTaskHolder {
    MuObjProcessTask* m_task;
    MuObjTaskHolder() { m_task = NULL; }
    ~MuObjTaskHolder() {
        delete m_task;
    }
};

struct MuObjBase {
    u32 m_flag : 1;
    u32 m_rest : 31;
    MuObjBase() { m_flag = 1; }
};

class MuObject : public MuObjBase {
public:
    nw4r::g3d::ResFile m_resFile;    // 0x04
    nw4r::g3d::ResMdl m_resMdl;      // 0x08
    nw4r::g3d::ScnMdl* m_scnMdl;     // 0x0c
    nw4r::g3d::ScnMdl* m_sceneModel; // 0x10
    gfModelAnimation* m_modelAnim;   // 0x14
    u32 m_18;                        // 0x18
    MuAnimIdxData* m_animIdxData;    // 0x1c
    MuAnimNameData* m_animNameData;  // 0x20
    ZeroWord m_24[4];                // 0x24
    u32 m_baseNode;                  // 0x34
    u8 m_38;                         // 0x38
    Vec3f m_trans;                   // 0x3c
    Vec3f m_rot;                     // 0x48
    Heaps::HeapType m_heapType;      // 0x54
    MuObjTaskHolder m_task;          // 0x58

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
    void changeMaterialTex(const char* matName, int texIndex, nw4r::g3d::ResFile* texFile);
    void changeMaterialTex(u32 matId, const char* texName, nw4r::g3d::ResFile* texFile);
    void changeAnimN(int animId, u32 flags, bool play, bool reset);
    void setAnimIdx(MuAnimIdxData* data, bool force);
    void setAnimName(MuAnimNameData* data, bool force);
    void setFrame(float frame);
    void setFrameNode(float frame);
    void setFrameVisible(float frame);
    void setFrameTex(float frame);
    void setFrameTexSrt(float frame);
    void setFrameMatCol(float frame);

    MuObject(const char* path, int drawPriority, int node, MuObject* src, nw4r::g3d::ResFile* textureSource, Heaps::HeapType heapType);
    void initFromFile(const char* path, int drawPriority, int node, nw4r::g3d::ResFile* textureSource, Heaps::HeapType heapType);
    void initFromObject(MuObject* src, int drawPriority, int node, Heaps::HeapType heapType);
    virtual ~MuObject();
    virtual void vfunc1();
};

static inline gfModelAnimation* newModelAnimIdx(void* mem, nw4r::g3d::ResMdl mdl, nw4r::g3d::ResFile file, int index, Heaps::HeapType heap) {
    return __ct__16gfModelAnimationFd(mem, &file, &mdl, true, index, heap);
}

static inline gfModelAnimation* newModelAnimName(void* mem, nw4r::g3d::ResMdl mdl, nw4r::g3d::ResFile file, const char* name, Heaps::HeapType heap) {
    return __ct1__16gfModelAnimationFd(mem, &file, &mdl, true, name, heap);
}

static inline u32 getScnMdlBufferFlags(nw4r::g3d::ResFile* file) {
    u32 flags = 0;
    if (file->HasResAnmClr()) {
        flags |= 0x10b;
    }
    if (file->HasResAnmTexPat()) {
        flags |= 0x3;
    }
    if (file->HasResAnmTexSrt()) {
        flags |= 0x204;
    }
    if (file->HasResAnmVis()) {
        flags |= 0x40;
    }
    if (file->HasResAnmShp()) {
        flags |= 0x7000;
    }
    return flags;
}

static inline u32 getRootNodeId(nw4r::g3d::ResMdl* mdl) {
    u8* cur = (u8*)mdl->GetResNode(0).ptr();
    while (true) {
        u32 off = *(u32*)(cur + 0x5c);
        u8* parent;
        if (off != 0) {
            parent = cur + off;
        } else {
            parent = NULL;
        }
        if (parent == NULL) {
            break;
        }
        cur = parent;
    }
    return cur != NULL ? *(u32*)(cur + 0xc) : 0;
}

MuObject::MuObject(nw4r::g3d::ResFile* modelSource, const char* modelNode, int drawPriority, nw4r::g3d::ResFile* textureSource, bool isByName, Heaps::HeapType heapType)
    : m_scnMdl(NULL), m_sceneModel(NULL), m_modelAnim(NULL), m_18(0), m_animIdxData(NULL), m_animNameData(NULL), m_baseNode(-1), m_38(0xff), m_heapType((Heaps::HeapType)0x2b) {
    MEMAllocator* allocator = gfHeapManager::getMEMAllocator(heapType);
    m_heapType = heapType;
    m_resFile = *modelSource;
    if (textureSource != NULL) {
        ResFile_Bind(&m_resFile, *textureSource);
    } else {
        ResFile_Bind(&m_resFile, m_resFile);
    }
    m_resMdl = ResFile_GetResMdlByName(&m_resFile, modelNode);
    u32 flags;
    if (isByName) {
        flags = getScnMdlBufferFlags(&m_resFile) | 0x10b;
    } else {
        flags = 0;
    }
    u32 size;
    nw4r::g3d::ScnMdl* scnMdl = ScnMdl_Construct(allocator, &size, m_resMdl, flags, 1, fn_801B0A28);
    if (drawPriority != 0) {
        scnMdl->SetPriorityDrawOpa(drawPriority);
        scnMdl->SetPriorityDrawXlu(drawPriority);
    }
    m_scnMdl = scnMdl;
    m_sceneModel = scnMdl;
    m_trans.m_x = m_trans.m_y = m_trans.m_z = 0.0f;
    m_rot.m_x = m_rot.m_y = m_rot.m_z = 0.0f;
    m_baseNode = getRootNodeId(&m_resMdl);
    if (!isByName) {
        return;
    }
    {
        gfModelAnimation* anim = (gfModelAnimation*)operator new(0x20, heapType);
        if (anim != NULL) {
            anim = newModelAnimName(anim, m_resMdl, m_resFile, modelNode, heapType);
        }
        gfModelAnimation::bind(scnMdl, anim);
        m_modelAnim = anim;
        *(u8*)((u8*)anim + 4) = 0;
        anim->setFrame(0.0f);
    }
}

MuObject::MuObject(nw4r::g3d::ResFile* modelSource, int node, int drawPriority, nw4r::g3d::ResFile* textureSource, bool isByIndex, Heaps::HeapType heapType)
    : m_scnMdl(NULL), m_sceneModel(NULL), m_modelAnim(NULL), m_18(0), m_animIdxData(NULL), m_animNameData(NULL), m_baseNode(-1), m_38(0xff), m_heapType((Heaps::HeapType)0x2b) {
    MEMAllocator* allocator = gfHeapManager::getMEMAllocator(heapType);
    m_heapType = heapType;
    m_resFile = *modelSource;
    if (textureSource != NULL) {
        ResFile_Bind(&m_resFile, *textureSource);
    } else {
        ResFile_Bind(&m_resFile, m_resFile);
    }
    m_resMdl = ResFile_GetResMdlByIndex(&m_resFile, node);
    u32 flags;
    if (isByIndex) {
        flags = getScnMdlBufferFlags(&m_resFile) | 0x10b;
    } else {
        flags = 0;
    }
    u32 size;
    nw4r::g3d::ScnMdl* scnMdl = ScnMdl_Construct(allocator, &size, m_resMdl, flags, 1, fn_801B0A28);
    if (drawPriority != 0) {
        scnMdl->SetPriorityDrawOpa(drawPriority);
        scnMdl->SetPriorityDrawXlu(drawPriority);
    }
    m_scnMdl = scnMdl;
    m_sceneModel = scnMdl;
    m_trans.m_x = m_trans.m_y = m_trans.m_z = 0.0f;
    m_rot.m_x = m_rot.m_y = m_rot.m_z = 0.0f;
    m_baseNode = getRootNodeId(&m_resMdl);
    if (!isByIndex) {
        return;
    }
    {
        gfModelAnimation* anim = (gfModelAnimation*)operator new(0x20, heapType);
        if (anim != NULL) {
            anim = newModelAnimIdx(anim, m_resMdl, m_resFile, node, heapType);
        }
        gfModelAnimation::bind(scnMdl, anim);
        m_modelAnim = anim;
        *(u8*)((u8*)anim + 4) = 0;
        anim->setFrame(0.0f);
    }
}

static inline void destroyModelAnim(gfModelAnimation* anim) {
    if (anim->m_anmObjChrRes != NULL) {
        anim->m_anmObjChrRes->Destroy();
    }
    if (anim->m_anmObjVisRes != NULL) {
        anim->m_anmObjVisRes->Destroy();
    }
    if (anim->m_anmObjTexPatRes != NULL) {
        anim->m_anmObjTexPatRes->Destroy();
    }
    if (anim->m_anmObjTexSrtRes != NULL) {
        anim->m_anmObjTexSrtRes->Destroy();
    }
    if (anim->m_anmObjMatClrRes != NULL) {
        anim->m_anmObjMatClrRes->Destroy();
    }
    if (anim->m_anmObjShpRes != NULL) {
        anim->m_anmObjShpRes->Destroy();
    }
    if (anim->m_resFile.ptr() != NULL) {
        if (*(u8*)((u8*)anim + 4) != 0) {
            gfHeapManager::free(anim->m_resFile.ptr());
            anim->m_resFile = nw4r::g3d::ResFile((void*)NULL);
        }
    }
    anim->m_anmObjChrRes = NULL;
    anim->m_anmObjVisRes = NULL;
    anim->m_anmObjTexPatRes = NULL;
    anim->m_anmObjTexSrtRes = NULL;
    anim->m_anmObjMatClrRes = NULL;
    anim->m_anmObjShpRes = NULL;
}

MuObject::MuObject(const char* path, int drawPriority, int node, MuObject* src, nw4r::g3d::ResFile* textureSource, Heaps::HeapType heapType)
    : m_scnMdl(NULL), m_sceneModel(NULL), m_modelAnim(NULL), m_18(0), m_animIdxData(NULL), m_animNameData(NULL), m_baseNode(-1), m_38(0xff), m_heapType(heapType) {
    if (src == NULL) {
        initFromFile(path, drawPriority, node, textureSource, heapType);
    } else {
        initFromObject(src, drawPriority, node, heapType);
    }
    m_trans.m_x = m_trans.m_y = m_trans.m_z = 0.0f;
    m_rot.m_x = m_rot.m_y = m_rot.m_z = 0.0f;
    m_baseNode = getRootNodeId(&m_resMdl);
}

MuObject::~MuObject() {
    gfModelAnimation* anim = m_modelAnim;
    if (anim != NULL) {
        destroyModelAnim(anim);
        gfHeapManager::free(m_modelAnim);
        m_modelAnim = NULL;
    }
    if (m_sceneModel != NULL) {
        ((nw4r::g3d::G3dObj*)m_sceneModel)->Destroy();
        m_sceneModel = NULL;
    }
}

void MuObject::vfunc1() {
}

static inline void* readFileBuffer(const char* path, Heaps::HeapType heapType) {
    void* buffer = NULL;
    gfFileIOHandle handle;
    if (handle.read(path, heapType, 0)) {
        buffer = handle.getBuffer();
        handle.getSize();
    }
    return buffer;
}

void MuObject::initFromFile(const char* path, int drawPriority, int node, nw4r::g3d::ResFile* textureSource, Heaps::HeapType heapType) {
    MEMAllocator* allocator = gfHeapManager::getMEMAllocator(heapType);
    void* buffer = readFileBuffer(path, heapType);
    m_resFile = nw4r::g3d::ResFile(buffer);
    if (buffer == NULL) {
        gfHeapManager::dumpAll();
    }
    nw4r::g3d::ResFile::Init(&m_resFile);
    ResFile_Bind(&m_resFile, textureSource != NULL ? *textureSource : m_resFile);
    m_resMdl = ResFile_GetResMdlByIndex(&m_resFile, node);
    u32 flags = getScnMdlBufferFlags(&m_resFile);
    u32 size;
    nw4r::g3d::ScnMdl* scnMdl = ScnMdl_Construct(allocator, &size, m_resMdl, flags | 0x10b, 1, fn_801B0A28);
    if (drawPriority != 0) {
        scnMdl->SetPriorityDrawOpa(drawPriority);
        scnMdl->SetPriorityDrawXlu(drawPriority);
    }
    gfModelAnimation* anim = (gfModelAnimation*)operator new(0x20, heapType);
    if (anim != NULL) {
        anim = newModelAnimIdx(anim, m_resMdl, m_resFile, node, heapType);
    }
    gfModelAnimation::bind(scnMdl, anim);
    m_scnMdl = scnMdl;
    m_sceneModel = scnMdl;
    m_modelAnim = anim;
    anim->setFrame(0.0f);
}

void MuObject::initFromObject(MuObject* src, int drawPriority, int node, Heaps::HeapType heapType) {
    MEMAllocator* allocator = gfHeapManager::getMEMAllocator(heapType);
    m_resFile = src->m_resFile;
    m_resMdl = src->m_resMdl;
    u32 flags = getScnMdlBufferFlags(&m_resFile);
    u32 size;
    nw4r::g3d::ScnMdl* scnMdl = ScnMdl_Construct(allocator, &size, m_resMdl, flags | 0x10b, 1, fn_801B0A28);
    if (drawPriority != 0) {
        scnMdl->SetPriorityDrawOpa(drawPriority);
        scnMdl->SetPriorityDrawXlu(drawPriority);
    }
    gfModelAnimation* anim = (gfModelAnimation*)operator new(0x20, heapType);
    if (anim != NULL) {
        anim = newModelAnimIdx(anim, m_resMdl, src->m_resFile, node, heapType);
    }
    gfModelAnimation::bind(scnMdl, anim);
    m_scnMdl = scnMdl;
    m_sceneModel = scnMdl;
    m_modelAnim = anim;
    *(u8*)((u8*)anim + 4) = 0;
    anim->setFrame(0.0f);
}

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

static inline void setChrAnimIdx(u32 animId, nw4r::g3d::ResMdl model, Heaps::HeapType heap, gfModelAnimation* modelAnim) {
    if (animId < modelAnim->m_resFile.GetResAnmChrNumEntries()) {
        setChrAnim(modelAnim->m_resFile.GetResAnmChr(animId), modelAnim, model, heap);
    }
}

static inline void setVisAnimIdx(u32 animId, nw4r::g3d::ResMdl model, Heaps::HeapType heap, gfModelAnimation* modelAnim) {
    if (animId < modelAnim->m_resFile.GetResAnmVisNumEntries()) {
        setVisAnim(modelAnim->m_resFile.GetResAnmVis(animId), modelAnim, model, heap);
    }
}

static inline void setTexSrtAnimIdx(u32 animId, nw4r::g3d::ResMdl model, Heaps::HeapType heap, gfModelAnimation* modelAnim) {
    if (animId < modelAnim->m_resFile.GetResAnmTexSrtNumEntries()) {
        setTexSrtAnim(modelAnim->m_resFile.GetResAnmTexSrt(animId), modelAnim, model, heap);
    }
}

static inline void setClrAnimIdx(u32 animId, nw4r::g3d::ResMdl model, Heaps::HeapType heap, gfModelAnimation* modelAnim) {
    if (animId < modelAnim->m_resFile.GetResAnmClrNumEntries()) {
        setClrAnim(modelAnim->m_resFile.GetResAnmClr(animId), modelAnim, model, heap);
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


static inline void changeNodeAnimIdx(MuObject* self, u32 index) {
    if (index < self->m_resFile.GetResAnmChrNumEntries()) {
        self->m_modelAnim->unbindNodeAnim(self->m_sceneModel);
        setChrAnimIdx(index, self->m_resMdl, self->m_heapType, self->m_modelAnim);
        self->m_modelAnim->bindNodeAnim(self->m_sceneModel);
        nw4r::g3d::AnmObjChrRes* o = self->m_modelAnim->m_anmObjChrRes;
        setPolicy(o, *(u32*)((u8*)o->m_anmChrFile.ptr() + 0x20));
        nw4r::g3d::ScnMdl* sceneModel = self->m_sceneModel;
        sceneModel->SetScnObjOption(2, 0);
        sceneModel->SetScnObjOption(5, 0);
    }
}

static inline void changeVisAnimIdx(MuObject* self, u32 index) {
    if (index < self->m_resFile.GetResAnmVisNumEntries()) {
        self->m_modelAnim->unbindVisibleAnim(self->m_sceneModel);
        setVisAnimIdx(index, self->m_resMdl, self->m_heapType, self->m_modelAnim);
        self->m_modelAnim->bindVisibleAnim(self->m_sceneModel);
        nw4r::g3d::AnmObjVisRes* o = self->m_modelAnim->m_anmObjVisRes;
        setPolicy(o, *(u32*)((u8*)o->m_anmVisFile.ptr() + 0x20));
        nw4r::g3d::ScnMdl* sceneModel = self->m_sceneModel;
        sceneModel->SetScnObjOption(2, 0);
        sceneModel->SetScnObjOption(5, 0);
    }
}

static inline void changeTexSrtAnimIdx(MuObject* self, u32 index) {
    if (index < self->m_resFile.GetResAnmTexSrtNumEntries()) {
        self->m_modelAnim->unbindTexSrtAnim(self->m_sceneModel);
        setTexSrtAnimIdx(index, self->m_resMdl, self->m_heapType, self->m_modelAnim);
        self->m_modelAnim->bindTexSrtAnim(self->m_sceneModel);
        nw4r::g3d::AnmObjTexSrtRes* o = self->m_modelAnim->m_anmObjTexSrtRes;
        setPolicy(o, *(u32*)((u8*)o->m_anmTexSrtFile.ptr() + 0x24));
        self->m_sceneModel->SetScnObjOption(3, 0);
    }
}

static inline void changeClrAnimIdx(MuObject* self, u32 index) {
    if (index < self->m_resFile.GetResAnmClrNumEntries()) {
        self->m_modelAnim->unbindMatColAnim(self->m_sceneModel);
        setClrAnimIdx(index, self->m_resMdl, self->m_heapType, self->m_modelAnim);
        self->m_modelAnim->bindMatColAnim(self->m_sceneModel);
        nw4r::g3d::AnmObjMatClrRes* o = self->m_modelAnim->m_anmObjMatClrRes;
        setPolicy(o, *(u32*)((u8*)o->m_anmMatClrFile.ptr() + 0x20));
        self->m_sceneModel->SetScnObjOption(3, 0);
    }
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

void MuObject::changeMaterialTex(const char* matName, int texIndex, nw4r::g3d::ResFile* texFile) {
    nw4r::g3d::ResFile* file = texFile == NULL ? &m_resFile : texFile;
    u8* tex = (u8*)file->GetResTex(texIndex).ptr();
    u32 off = *(u32*)(tex + 0x14);
    const char* texName = off != 0 ? (const char*)(tex + off) : NULL;
    changeMaterialTex(m_resMdl.GetResMat(matName)->m_id, texName, texFile);
}

void MuObject::changeMaterialTex(u32 matId, const char* texName, nw4r::g3d::ResFile* texFile) {
    MatAccess access(m_scnMdl, matId);
    nw4r::g3d::ResTex tex(NULL);
    nw4r::g3d::ResTexObj texObj(CopiedMatAccess_GetResTexObj(&access, false));
    GXTexObj* obj = texObj.GetTexObj(GX_TEXMAP0);
    if (texFile == NULL) {
        texFile = &m_resFile;
    }
    tex = texFile->GetResTex(texName);
    if ((*(u32*)((u8*)tex.ptr() + 0x18)) & 1) {
        u8* pltt = fn_8018D310(texFile, texName);
        void* tlutObjPtr = fn_801AFF94(&access, false);
        GXTlutObj* tlut = fn_80190DC8(&tlutObjPtr, 0);
        GXBool mipmap;
        f32 maxLod;
        f32 minLod;
        GXTexFmt fmt;
        u16 height;
        u16 width;
        void* image;
        fn_80192B00(&tex, &image, &width, &height, &fmt, &minLod, &maxLod, &mipmap);
        s32 plttOff = *(s32*)(pltt + 0x10);
        s32 mask = (-plttOff | plttOff) >> 31;
        void* plttData = (void*)((u32)(pltt + plttOff) & mask);
        GXInitTlutObj(tlut, plttData, (GXTlutFmt) * (u32*)(pltt + 0x18), *(u16*)(pltt + 0x1c));
        GXLoadTlut(tlut, GX_TLUT0);
        GXInitTexObjCI(obj, image, width, height, fmt, GX_CLAMP, GX_CLAMP, mipmap, 0);
        GXLoadTexObj(obj, GX_TEXMAP0);
        fn_801AFF94(&access, false);
        CopiedMatAccess_GetResTexObj(&access, false);
    } else {
        GXBool mipmap;
        f32 maxLod;
        f32 minLod;
        GXTexFmt fmt;
        u16 height;
        u16 width;
        void* image;
        fn_80192A44(&tex, &image, &width, &height, &fmt, &minLod, &maxLod, &mipmap);
        GXTexWrapMode wrapS = GXGetTexObjWrapS(obj);
        GXTexWrapMode wrapT = GXGetTexObjWrapT(obj);
        GXInitTexObj(obj, image, width, height, fmt, wrapS, wrapT, mipmap);
        CopiedMatAccess_GetResTexObj(&access, false);
    }
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

void MuObject::setAnimIdx(MuAnimIdxData* data, bool force) {
    bool changed = false;
    if (force) {
        if (m_animIdxData != NULL) {
            if (m_animIdxData->m_index != data->m_index) {
                changed = true;
            }
        } else {
            changed = true;
        }
    }
    m_animIdxData = data;
    if (m_animIdxData->m_flags & 1) {
        if (m_modelAnim->m_anmObjChrRes != NULL) {
            if (changed) {
                changeNodeAnimIdx(this, data->m_index);
            }
            setFrameNode(data->m_frame);
            m_modelAnim->m_anmObjChrRes->SetUpdateRate(1.0f);
        }
    }
    if (m_animIdxData->m_flags & 2) {
        if (m_modelAnim->m_anmObjVisRes != NULL) {
            if (changed) {
                changeVisAnimIdx(this, data->m_index);
            }
            setFrameVisible(data->m_frame);
            m_modelAnim->m_anmObjVisRes->SetUpdateRate(1.0f);
        }
    }
    if (m_animIdxData->m_flags & 4) {
        if (m_modelAnim->m_anmObjTexPatRes != NULL) {
            if (changed) {
                changeTexPatAnim(data->m_index);
            }
            setFrameTex(data->m_frame);
            m_modelAnim->m_anmObjTexPatRes->SetUpdateRate(1.0f);
        }
    }
    if (m_animIdxData->m_flags & 8) {
        if (m_modelAnim->m_anmObjTexSrtRes != NULL) {
            if (changed) {
                changeTexSrtAnimIdx(this, data->m_index);
            }
            setFrameTexSrt(data->m_frame);
            m_modelAnim->m_anmObjTexSrtRes->SetUpdateRate(1.0f);
        }
    }
    if (m_animIdxData->m_flags & 16) {
        if (m_modelAnim->m_anmObjMatClrRes != NULL) {
            if (changed) {
                changeClrAnimIdx(this, data->m_index);
            }
            setFrameMatCol(data->m_frame);
            m_modelAnim->m_anmObjMatClrRes->SetUpdateRate(1.0f);
        }
    }
}

void MuObject::setAnimName(MuAnimNameData* data, bool force) {
    const char* name = data->m_name;
    bool changed = false;
    if (force) {
        if (m_animNameData != NULL) {
            if (strcmp(m_animNameData->m_name, data->m_name) != 0) {
                changed = true;
            }
        } else {
            changed = true;
        }
    }
    m_animNameData = data;
    {
        bool valid = true;
        if (m_animNameData->m_flags & 1) {
            if (changed || m_modelAnim->m_anmObjChrRes == NULL) {
                nw4r::g3d::ResAnmChr anim = ResFile_GetResAnmChrByName(&m_resFile, name);
                if (!anim.IsValid()) {
                    valid = false;
                } else {
                    bindNodeAnimImpl(this, anim);
                    valid = true;
                }
            }
            if (valid) {
                setFrameNode(data->m_frame);
                m_modelAnim->m_anmObjChrRes->SetUpdateRate(1.0f);
            }
        }
    }
    {
        bool valid = true;
        if (m_animNameData->m_flags & 2) {
            if (changed || m_modelAnim->m_anmObjVisRes == NULL) {
                nw4r::g3d::ResAnmVis anim = ResFile_GetResAnmVisByName(&m_resFile, name);
                if (!anim.IsValid()) {
                    valid = false;
                } else {
                    bindVisAnimImpl(this, anim);
                    valid = true;
                }
            }
            if (valid) {
                setFrameVisible(data->m_frame);
                m_modelAnim->m_anmObjVisRes->SetUpdateRate(1.0f);
            }
        }
    }
    {
        bool valid = true;
        if (m_animNameData->m_flags & 4) {
            if (changed || m_modelAnim->m_anmObjTexPatRes == NULL) {
                nw4r::g3d::ResAnmTexPat anim = ResFile_GetResAnmTexPatByName(&m_resFile, name);
                if (!anim.IsValid()) {
                    valid = false;
                } else {
                    bindTexPatAnimImpl(this, anim);
                    valid = true;
                }
            }
            if (valid) {
                setFrameTex(data->m_frame);
                m_modelAnim->m_anmObjTexPatRes->SetUpdateRate(1.0f);
            }
        }
    }
    {
        bool valid = true;
        if (m_animNameData->m_flags & 8) {
            if (changed || m_modelAnim->m_anmObjTexSrtRes == NULL) {
                nw4r::g3d::ResAnmTexSrt anim = ResFile_GetResAnmTexSrtByName(&m_resFile, name);
                if (!anim.IsValid()) {
                    valid = false;
                } else {
                    bindTexSrtAnimImpl(this, anim);
                    valid = true;
                }
            }
            if (valid) {
                setFrameTexSrt(data->m_frame);
                m_modelAnim->m_anmObjTexSrtRes->SetUpdateRate(1.0f);
            }
        }
    }
    {
        bool valid = true;
        if (m_animNameData->m_flags & 16) {
            if (changed || m_modelAnim->m_anmObjMatClrRes == NULL) {
                nw4r::g3d::ResAnmClr anim = ResFile_GetResAnmClrByName(&m_resFile, name);
                if (!anim.IsValid()) {
                    valid = false;
                } else {
                    bindClrAnimImpl(this, anim);
                    valid = true;
                }
            }
            if (valid) {
                setFrameMatCol(data->m_frame);
                m_modelAnim->m_anmObjMatClrRes->SetUpdateRate(1.0f);
            }
        }
    }
}
