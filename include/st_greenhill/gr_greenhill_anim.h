#pragma once

// The Green Hill gimmicks bind their animations with the same sequence as gf_model.h's helpers, but their animation
// index stays a full 32-bit value (the shared helpers take a u8). These copies keep the original code shape.

#include <gf/gf_model.h>
#include <gr/ground.h>

static inline void grGreenhillBindChr(u32 animId, nw4r::g3d::ResMdl model, gfModelAnimation* modelAnim, Heaps::HeapType heap) {
    if (animId < modelAnim->m_resFile.GetResAnmChrNumEntries()) {
        int instanceSize;
        nw4r::g3d::ResAnmChr anim = modelAnim->m_resFile.GetResAnmChr((u32)animId);
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
}

static inline void grGreenhillBindTexPat(u32 animId, nw4r::g3d::ResMdl model, gfModelAnimation* modelAnim, Heaps::HeapType heap) {
    if (animId < modelAnim->m_resFile.GetResAnmTexPatNumEntries()) {
        int instanceSize;
        nw4r::g3d::ResAnmTexPat anim = modelAnim->m_resFile.GetResAnmTexPat((u32)animId);
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
}

static inline void grGreenhillBindTexSrt(u32 animId, nw4r::g3d::ResMdl model, gfModelAnimation* modelAnim, Heaps::HeapType heap) {
    if (animId < modelAnim->m_resFile.GetResAnmTexSrtNumEntries()) {
        int instanceSize;
        nw4r::g3d::ResAnmTexSrt anim = modelAnim->m_resFile.GetResAnmTexSrt((u32)animId);
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
}

static inline void grGreenhillBindMatClr(u32 animId, nw4r::g3d::ResMdl model, gfModelAnimation* modelAnim, Heaps::HeapType heap) {
    if (animId < modelAnim->m_resFile.GetResAnmClrNumEntries()) {
        int instanceSize;
        nw4r::g3d::ResAnmClr anim = modelAnim->m_resFile.GetResAnmClr((u32)animId);
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
}

static inline void grGreenhillBindVis(u32 animId, nw4r::g3d::ResMdl model, gfModelAnimation* modelAnim, Heaps::HeapType heap) {
    if (animId < modelAnim->m_resFile.GetResAnmVisNumEntries()) {
        int instanceSize;
        nw4r::g3d::ResAnmVis anim = modelAnim->m_resFile.GetResAnmVis((u32)animId);
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
}

// Shared body of the Check, Break and GuestLine setMotion: switch the model to animation animId (below animCount),
// rebinding every animation type, and report the frame count of the new animation.
static inline void grGreenhillSetMotion(Ground* ground, u8& currentAnim, u32 animCount, u32 animId, bool shouldLoop,
                                        bool force, float* frameCount) {
    if (currentAnim == animId && force == 0) {
        return;
    }

    nw4r::g3d::ScnMdl* sceneMdl = *ground->m_sceneModels;
    if (sceneMdl == NULL) {
        return;
    }

    gfModelAnimation* modelAnim = *ground->m_modelAnims;
    if (modelAnim == NULL) {
        return;
    }

    nw4r::g3d::ResMdl model = sceneMdl->m_resMdl;
    if (!model.IsValid()) {
        return;
    }

    modelAnim->unbindNodeAnim(sceneMdl);
    modelAnim->unbindVisibleAnim(sceneMdl);
    modelAnim->unbindTexAnim(sceneMdl);
    modelAnim->unbindTexSrtAnim(sceneMdl);
    modelAnim->unbindMatColAnim(sceneMdl);
    currentAnim = animId;

    if (animId >= animCount) {
        return;
    }

    bool result = (modelAnim->m_resFile.GetResAnmChrNumEntries() > animId);
    if (result) {
        grGreenhillBindChr(animId, model, modelAnim, Heaps::StageInstance);
    }

    result = (modelAnim->m_resFile.GetResAnmTexPatNumEntries() > animId);
    if (result) {
        grGreenhillBindTexPat(animId, model, modelAnim, Heaps::StageInstance);
    }

    result = (modelAnim->m_resFile.GetResAnmTexSrtNumEntries() > animId);
    if (result) {
        grGreenhillBindTexSrt(animId, model, modelAnim, Heaps::StageInstance);
    }

    result = (modelAnim->m_resFile.GetResAnmClrNumEntries() > animId);
    if (result) {
        grGreenhillBindMatClr(animId, model, modelAnim, Heaps::StageInstance);
    }

    result = (modelAnim->m_resFile.GetResAnmVisNumEntries() > animId);
    if (result) {
        grGreenhillBindVis(animId, model, modelAnim, Heaps::StageInstance);
    }

    gfModelAnimation::bind(sceneMdl, modelAnim);
    modelAnim->setFrame(0.0);
    modelAnim->setUpdateRate(1.0);
    modelAnim->setLoop(shouldLoop);

    if (frameCount != NULL) {
        *frameCount = modelAnim->getFrameCount();
    }
}
