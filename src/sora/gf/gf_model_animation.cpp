#include <gf/gf_model.h>

namespace nw4r {
    namespace g3d {
        typedef f32 (*PlayPolicyFunc)(f32, f32, f32);

        // Minimal view of the ScnMdl vtable slots used here.
        struct ScnMdlAnmIf {
            virtual void v0();
            virtual void v1();
            virtual void v2();
            virtual void v3();
            virtual void v4();
            virtual void v5();
            virtual void v6();
            virtual void v7();
            virtual void v8();
            virtual void v9();
            virtual void v10();
            virtual void SetAnmObj(G3dObj* obj, int type);
            virtual void RemoveAnmObj(G3dObj* obj);
            virtual void RemoveAnmObjType(int type);
            virtual G3dObj* GetAnmObj(int type);
        };
    }
}

extern "C" {
f32 fn_8019D9E4(f32, f32, f32);
f32 fn_8019D9EC(f32, f32, f32);
nw4r::g3d::ResAnmChr fn_8018D5D4(nw4r::g3d::ResFile*, const char*);
nw4r::g3d::ResAnmVis fn_8018D7DC(nw4r::g3d::ResFile*, const char*);
nw4r::g3d::ResAnmClr fn_8018D9E4(nw4r::g3d::ResFile*, const char*);
nw4r::g3d::ResAnmTexPat fn_8018DBEC(nw4r::g3d::ResFile*, const char*);
nw4r::g3d::ResAnmTexSrt fn_8018DDF4(nw4r::g3d::ResFile*, const char*);
nw4r::g3d::ResAnmShp fn_8018DFFC(nw4r::g3d::ResFile*, const char*);
}

using namespace nw4r::g3d;

static inline PlayPolicyFunc getPolicy(bool loop) {
    static PlayPolicyFunc policies[2] = { fn_8019D9E4, fn_8019D9EC };
    return policies[loop];
}

static inline void setPolicy(void* anmObj, PlayPolicyFunc policy) {
    *(PlayPolicyFunc*)((char*)anmObj + 0x28) = policy;
}

void gfModelAnimation::bind(ScnMdl* sceneModel, gfModelAnimation* modelAnim) {
    if (modelAnim->m_anmObjChrRes) {
        ((ScnMdlAnmIf*)sceneModel)->SetAnmObj(modelAnim->m_anmObjChrRes, 0);
    }
    if (modelAnim->m_anmObjVisRes) {
        ((ScnMdlAnmIf*)sceneModel)->SetAnmObj(modelAnim->m_anmObjVisRes, 1);
    }
    if (modelAnim->m_anmObjTexPatRes) {
        ((ScnMdlAnmIf*)sceneModel)->SetAnmObj(modelAnim->m_anmObjTexPatRes, 3);
    }
    if (modelAnim->m_anmObjTexSrtRes) {
        ((ScnMdlAnmIf*)sceneModel)->SetAnmObj(modelAnim->m_anmObjTexSrtRes, 4);
    }
    if (modelAnim->m_anmObjMatClrRes) {
        ((ScnMdlAnmIf*)sceneModel)->SetAnmObj(modelAnim->m_anmObjMatClrRes, 2);
    }
    if (modelAnim->m_anmObjShpRes) {
        ((ScnMdlAnmIf*)sceneModel)->SetAnmObj(modelAnim->m_anmObjShpRes, 5);
    }
}

#define BIND_FN(name, field, type)                              \
    void gfModelAnimation::name(ScnMdl* sceneModel) {           \
        if (field) {                                            \
            ((ScnMdlAnmIf*)sceneModel)->SetAnmObj(field, type); \
        }                                                       \
    }

BIND_FN(bindNodeAnim, m_anmObjChrRes, 0)
BIND_FN(bindVisibleAnim, m_anmObjVisRes, 1)
BIND_FN(bindTexAnim, m_anmObjTexPatRes, 3)
BIND_FN(bindTexSrtAnim, m_anmObjTexSrtRes, 4)
BIND_FN(bindMatColAnim, m_anmObjMatClrRes, 2)
BIND_FN(bindShapeAnim, m_anmObjShpRes, 5)

void gfModelAnimation::unbind(ScnMdl* sceneModel) {
    static const int types[6] = { 0, 1, 2, 3, 4, 5 };
    for (int i = 0; i < 6; i++) {
        G3dObj* obj = ((ScnMdlAnmIf*)sceneModel)->GetAnmObj(types[i]);
        if (obj) {
            ((ScnMdlAnmIf*)sceneModel)->RemoveAnmObj(obj);
        }
    }
}

#define UNBIND_FN(name, field, type)                  \
    void gfModelAnimation::name(ScnMdl* sceneModel) { \
        ScnMdlAnmIf* mdl = (ScnMdlAnmIf*)sceneModel;  \
        G3dObj* obj = mdl->GetAnmObj(type);           \
        if (obj) {                                    \
            mdl->RemoveAnmObjType(type);              \
        }                                             \
        if (field && (G3dObj*)field == obj) {         \
            ((G3dObj*)field)->Destroy();              \
            field = NULL;                             \
        }                                             \
    }

UNBIND_FN(unbindNodeAnim, m_anmObjChrRes, 0)
UNBIND_FN(unbindVisibleAnim, m_anmObjVisRes, 1)
UNBIND_FN(unbindTexAnim, m_anmObjTexPatRes, 3)
UNBIND_FN(unbindTexSrtAnim, m_anmObjTexSrtRes, 4)
UNBIND_FN(unbindMatColAnim, m_anmObjMatClrRes, 2)
UNBIND_FN(unbindShapeAnim, m_anmObjShpRes, 5)

gfModelAnimation::gfModelAnimation(ResFile* resFile, ResMdl* resMdl, bool doBind, u32 animIndex, HeapType heapType) {
    int instanceSize;
    MEMAllocator* allocator = gfHeapManager::getMEMAllocator(heapType);
    m_resFile = *resFile;
    _spacer[0] = 1;
    m_anmObjChrRes = NULL;
    m_anmObjVisRes = NULL;
    m_anmObjTexPatRes = NULL;
    m_anmObjTexSrtRes = NULL;
    m_anmObjMatClrRes = NULL;
    m_anmObjShpRes = NULL;

    if (m_resFile.HasResAnmChr() && animIndex < m_resFile.GetResAnmChrNumEntries()) {
        m_anmObjChrRes = AnmObjChrRes::Construct(allocator, &instanceSize, resFile->GetResAnmChr(animIndex), *resMdl, false);
        if (doBind) {
            m_anmObjChrRes->Bind(*resMdl);
        }
    }
    if (m_resFile.HasResAnmVis() && animIndex < m_resFile.GetResAnmVisNumEntries()) {
        m_anmObjVisRes = AnmObjVisRes::Construct(allocator, &instanceSize, resFile->GetResAnmVis(animIndex), *resMdl);
        if (doBind) {
            m_anmObjVisRes->Bind(*resMdl);
        }
    }
    if (m_resFile.HasResAnmTexPat() && animIndex < m_resFile.GetResAnmTexPatNumEntries()) {
        m_anmObjTexPatRes = AnmObjTexPatRes::Construct(allocator, &instanceSize, resFile->GetResAnmTexPat(animIndex), *resMdl, false);
        if (doBind) {
            m_anmObjTexPatRes->Bind(*resMdl);
        }
    }
    if (m_resFile.HasResAnmTexSrt() && animIndex < m_resFile.GetResAnmTexSrtNumEntries()) {
        m_anmObjTexSrtRes = AnmObjTexSrtRes::Construct(allocator, &instanceSize, resFile->GetResAnmTexSrt(animIndex), *resMdl, false);
        if (doBind) {
            m_anmObjTexSrtRes->Bind(*resMdl);
        }
    }
    if (m_resFile.HasResAnmClr() && animIndex < m_resFile.GetResAnmClrNumEntries()) {
        m_anmObjMatClrRes = AnmObjMatClrRes::Construct(allocator, &instanceSize, resFile->GetResAnmClr(animIndex), *resMdl, false);
        if (doBind) {
            m_anmObjMatClrRes->Bind(*resMdl);
        }
    }
    if (m_resFile.HasResAnmShp() && animIndex < m_resFile.GetResAnmShpNumEntries()) {
        m_anmObjShpRes = AnmObjShpRes::Construct(allocator, &instanceSize, resFile->GetResAnmShp(animIndex), *resMdl, false);
        if (doBind) {
            m_anmObjShpRes->Bind(*resMdl);
        }
    }
}

gfModelAnimation::gfModelAnimation(ResFile* resFile, ResMdl* resMdl, bool doBind, const char* animName, HeapType heapType) {
    int instanceSize;
    MEMAllocator* allocator = gfHeapManager::getMEMAllocator(heapType);
    m_resFile = *resFile;
    _spacer[0] = 1;
    m_anmObjChrRes = NULL;
    m_anmObjVisRes = NULL;
    m_anmObjTexPatRes = NULL;
    m_anmObjTexSrtRes = NULL;
    m_anmObjMatClrRes = NULL;
    m_anmObjShpRes = NULL;

    {
        ResAnmChr anim = fn_8018D5D4(resFile, animName);
        if (anim.IsValid()) {
            m_anmObjChrRes = AnmObjChrRes::Construct(allocator, &instanceSize, anim, *resMdl, false);
            if (doBind) {
                m_anmObjChrRes->Bind(*resMdl);
            }
        }
    }
    {
        ResAnmVis anim = fn_8018D7DC(resFile, animName);
        if (anim.IsValid()) {
            m_anmObjVisRes = AnmObjVisRes::Construct(allocator, &instanceSize, anim, *resMdl);
            if (doBind) {
                m_anmObjVisRes->Bind(*resMdl);
            }
        }
    }
    {
        ResAnmTexPat anim = fn_8018DBEC(resFile, animName);
        if (anim.IsValid()) {
            m_anmObjTexPatRes = AnmObjTexPatRes::Construct(allocator, &instanceSize, anim, *resMdl, false);
            if (doBind) {
                m_anmObjTexPatRes->Bind(*resMdl);
            }
        }
    }
    {
        ResAnmTexSrt anim = fn_8018DDF4(resFile, animName);
        if (anim.IsValid()) {
            m_anmObjTexSrtRes = AnmObjTexSrtRes::Construct(allocator, &instanceSize, anim, *resMdl, false);
            if (doBind) {
                m_anmObjTexSrtRes->Bind(*resMdl);
            }
        }
    }
    {
        ResAnmClr anim = fn_8018D9E4(resFile, animName);
        if (anim.IsValid()) {
            m_anmObjMatClrRes = AnmObjMatClrRes::Construct(allocator, &instanceSize, anim, *resMdl, false);
            if (doBind) {
                m_anmObjMatClrRes->Bind(*resMdl);
            }
        }
    }
    {
        ResAnmShp anim = fn_8018DFFC(resFile, animName);
        if (anim.IsValid()) {
            m_anmObjShpRes = AnmObjShpRes::Construct(allocator, &instanceSize, anim, *resMdl, false);
            if (doBind) {
                m_anmObjShpRes->Bind(*resMdl);
            }
        }
    }
}

void gfModelAnimation::setLoop(bool shouldLoop) {
    PlayPolicyFunc policy = getPolicy(shouldLoop);
    if (m_anmObjChrRes) setPolicy(m_anmObjChrRes, policy);
    if (m_anmObjVisRes) setPolicy(m_anmObjVisRes, policy);
    if (m_anmObjTexPatRes) setPolicy(m_anmObjTexPatRes, policy);
    if (m_anmObjTexSrtRes) setPolicy(m_anmObjTexSrtRes, policy);
    if (m_anmObjMatClrRes) setPolicy(m_anmObjMatClrRes, policy);
    if (m_anmObjShpRes) setPolicy(m_anmObjShpRes, policy);
}

#define SETLOOP_FN(name, field)                        \
    void gfModelAnimation::name(bool shouldLoop) {     \
        PlayPolicyFunc policy = getPolicy(shouldLoop); \
        if (field) {                                   \
            setPolicy(field, policy);                  \
        }                                              \
    }

SETLOOP_FN(setLoopNode, m_anmObjChrRes)
SETLOOP_FN(setLoopVisible, m_anmObjVisRes)
SETLOOP_FN(setLoopTex, m_anmObjTexPatRes)
SETLOOP_FN(setLoopTexSrt, m_anmObjTexSrtRes)
SETLOOP_FN(setLoopMatCol, m_anmObjMatClrRes)

u32 gfModelAnimation::getFrameCount() {
    int count = 0;
    if (m_anmObjChrRes) {
        int len = m_anmObjChrRes->m_anmChrFile->m_animLength;
        count = count > len ? count : len;
    }
    if (m_anmObjVisRes) {
        int len = m_anmObjVisRes->m_anmVisFile->m_animLength;
        count = count > len ? count : len;
    }
    if (m_anmObjTexPatRes) {
        int len = m_anmObjTexPatRes->m_anmTexPatFile->m_animLength;
        count = count > len ? count : len;
    }
    if (m_anmObjTexSrtRes) {
        int len = m_anmObjTexSrtRes->m_anmTexSrtFile->m_animLength;
        count = count > len ? count : len;
    }
    if (m_anmObjMatClrRes) {
        int len = m_anmObjMatClrRes->m_anmMatClrFile->m_animLength;
        count = count > len ? count : len;
    }
    if (m_anmObjShpRes) {
        int len = m_anmObjShpRes->m_anmShpFile->m_animLength;
        count = count > len ? count : len;
    }
    return count;
}

void gfModelAnimation::setFrame(float frame) {
    if (m_anmObjChrRes) m_anmObjChrRes->SetFrame(frame);
    if (m_anmObjVisRes) m_anmObjVisRes->SetFrame(frame);
    if (m_anmObjTexPatRes) m_anmObjTexPatRes->SetFrame(frame);
    if (m_anmObjTexSrtRes) m_anmObjTexSrtRes->SetFrame(frame);
    if (m_anmObjMatClrRes) m_anmObjMatClrRes->SetFrame(frame);
    if (m_anmObjShpRes) m_anmObjShpRes->SetFrame(frame);
}

float gfModelAnimation::getFrame() {
    if (m_anmObjChrRes) return m_anmObjChrRes->GetFrame();
    if (m_anmObjVisRes) return m_anmObjVisRes->GetFrame();
    if (m_anmObjTexPatRes) return m_anmObjTexPatRes->GetFrame();
    if (m_anmObjTexSrtRes) return m_anmObjTexSrtRes->GetFrame();
    if (m_anmObjMatClrRes) return m_anmObjMatClrRes->GetFrame();
    if (m_anmObjShpRes) return m_anmObjShpRes->GetFrame();
    return 0.0f;
}

void gfModelAnimation::setUpdateRate(float updateRate) {
    if (m_anmObjChrRes) m_anmObjChrRes->SetUpdateRate(updateRate);
    if (m_anmObjVisRes) m_anmObjVisRes->SetUpdateRate(updateRate);
    if (m_anmObjTexPatRes) m_anmObjTexPatRes->SetUpdateRate(updateRate);
    if (m_anmObjTexSrtRes) m_anmObjTexSrtRes->SetUpdateRate(updateRate);
    if (m_anmObjMatClrRes) m_anmObjMatClrRes->SetUpdateRate(updateRate);
    if (m_anmObjShpRes) m_anmObjShpRes->SetUpdateRate(updateRate);
}

float gfModelAnimation::getUpdateRate() {
    if (m_anmObjChrRes) return m_anmObjChrRes->GetUpdateRate();
    if (m_anmObjVisRes) return m_anmObjVisRes->GetUpdateRate();
    if (m_anmObjTexPatRes) return m_anmObjTexPatRes->GetUpdateRate();
    if (m_anmObjTexSrtRes) return m_anmObjTexSrtRes->GetUpdateRate();
    if (m_anmObjMatClrRes) return m_anmObjMatClrRes->GetUpdateRate();
    if (m_anmObjShpRes) return m_anmObjShpRes->GetUpdateRate();
    return 0.0f;
}
