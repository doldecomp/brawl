#pragma once

#include <StaticAssert.h>
#include <nw4r/g3d/g3d_anmchr.h>
#include <nw4r/g3d/g3d_anmclr.h>
#include <nw4r/g3d/g3d_anmshp.h>
#include <nw4r/g3d/g3d_anmtexpat.h>
#include <nw4r/g3d/g3d_anmtexsrt.h>
#include <nw4r/g3d/g3d_anmvis.h>
#include <nw4r/g3d/g3d_resfile.h>
#include <nw4r/g3d/g3d_resmdl.h>
#include <nw4r/g3d/g3d_scnmdl.h>
#include <gf/gf_heap_manager.h>
#include <types.h>

class gfModelAnimation {
public:
    nw4r::g3d::ResFile m_resFile;
    char _spacer[4];

    nw4r::g3d::AnmObjVisRes* m_anmObjVisRes;
    nw4r::g3d::AnmObjChrRes* m_anmObjChrRes;
    nw4r::g3d::AnmObjTexPatRes* m_anmObjTexPatRes;
    nw4r::g3d::AnmObjTexSrtRes* m_anmObjTexSrtRes;
    nw4r::g3d::AnmObjMatClrRes* m_anmObjMatClrRes;
    nw4r::g3d::AnmObjShpRes* m_anmObjShpRes;

    gfModelAnimation(nw4r::g3d::ResFile* resFile, nw4r::g3d::ResMdl* resMdl, bool doBind, u32 animIndex, HeapType heapType);
    gfModelAnimation(nw4r::g3d::ResFile* resFile, nw4r::g3d::ResMdl* resMdl, bool doBind, const char* animName, HeapType heapType);

    u32 getFrameCount();
    float getFrame();
    void setFrame(float frame);
    float getUpdateRate();
    void setUpdateRate(float updateRate);
    void setLoop(bool shouldLoop);
    void setLoopNode(bool shouldLoop);
    void setLoopVisible(bool shouldLoop);
    void setLoopTex(bool shouldLoop);
    void setLoopTexSrt(bool shouldLoop);
    void setLoopMatCol(bool shouldLoop);
    void unbindNodeAnim(nw4r::g3d::ScnMdl* sceneModel);
    void unbindVisibleAnim(nw4r::g3d::ScnMdl* sceneModel);
    void unbindTexAnim(nw4r::g3d::ScnMdl* sceneModel);
    void unbindTexSrtAnim(nw4r::g3d::ScnMdl* sceneModel);
    void unbindMatColAnim(nw4r::g3d::ScnMdl* sceneModel);
    void unbindShapeAnim(nw4r::g3d::ScnMdl* sceneModel);
    void bindNodeAnim(nw4r::g3d::ScnMdl* sceneModel);
    void bindVisibleAnim(nw4r::g3d::ScnMdl* sceneModel);
    void bindTexAnim(nw4r::g3d::ScnMdl* sceneModel);
    void bindTexSrtAnim(nw4r::g3d::ScnMdl* sceneModel);
    void bindMatColAnim(nw4r::g3d::ScnMdl* sceneModel);
    void bindShapeAnim(nw4r::g3d::ScnMdl* sceneModel);

    static void unbind(nw4r::g3d::ScnMdl* sceneModel);
    static void bind(nw4r::g3d::ScnMdl* sceneModel, gfModelAnimation* modelAnim);
};
static_assert(sizeof(gfModelAnimation) == 32, "Class is wrong size!");

// Size: 32

//Various inlines used by menu objects effects, and many ground objects
//TODO: find better names for these functions
inline void setVisibilityAnim(u8 animId,nw4r::g3d::ResMdl model, gfModelAnimation* modelAnim, Heaps::HeapType heap) {
//    if (animId < modelAnim->m_resFile.GetResAnmClrNumEntries())
        int instanceSize;
        nw4r::g3d::ResAnmVis anim = modelAnim->m_resFile.GetResAnmVis((u32)animId);

        MEMAllocator* allocator = gfHeapManager::getMEMAllocator(heap);
        if (anim.IsValid())
        {
            nw4r::g3d::AnmObjVisRes* anmObj = nw4r::g3d::AnmObjVisRes::Construct(allocator, &instanceSize, anim, model);
            if (anmObj != NULL)
            {
                anmObj->Bind(model);

                if (modelAnim->m_anmObjVisRes != NULL)
                {
                    modelAnim->m_anmObjVisRes->Destroy();
                }

                modelAnim->m_anmObjVisRes = anmObj;
            }
        }
  //  }
}

inline void setVisibilityAnim2(u8 animId,nw4r::g3d::ResMdl model, gfModelAnimation* modelAnim, Heaps::HeapType heap) {
    if (animId < modelAnim->m_resFile.GetResAnmVisNumEntries()) {
 //       int instanceSize;
        setVisibilityAnim(animId,model, modelAnim, heap);
    }
}


inline void setChrAnim(u8 animId,nw4r::g3d::ResMdl model, gfModelAnimation* modelAnim, Heaps::HeapType heap) {
//    if (animId < modelAnim->m_resFile.GetResAnmClrNumEntries())
        int instanceSize;
        nw4r::g3d::ResAnmChr anim = modelAnim->m_resFile.GetResAnmChr((u32)animId);

        MEMAllocator* allocator = gfHeapManager::getMEMAllocator(heap);
        if (anim.IsValid())
        {
            nw4r::g3d::AnmObjChrRes* anmObj = nw4r::g3d::AnmObjChrRes::Construct(allocator, &instanceSize, anim, model, false);
            if (anmObj != NULL)
            {
                anmObj->Bind(model);

                if (modelAnim->m_anmObjChrRes != NULL)
                {
                    modelAnim->m_anmObjChrRes->Destroy();
                }

                modelAnim->m_anmObjChrRes = anmObj;
            }
        }
  //  }
}

inline void setChrAnim2(u8 animId,nw4r::g3d::ResMdl model, gfModelAnimation* modelAnim, Heaps::HeapType heap) {
    if (animId < modelAnim->m_resFile.GetResAnmChrNumEntries()) {
 //       int instanceSize;
        setChrAnim(animId,model, modelAnim,heap);
    }
}


inline void setTexPatAnim(u8 animId,nw4r::g3d::ResMdl model, gfModelAnimation* modelAnim, Heaps::HeapType heap) {
//    if (animId < modelAnim->m_resFile.GetResAnmClrNumEntries())
        int instanceSize;
        nw4r::g3d::ResAnmTexPat anim = modelAnim->m_resFile.GetResAnmTexPat((u32)animId);

        if (anim.IsValid())
        {
            MEMAllocator* allocator = gfHeapManager::getMEMAllocator(heap);
            nw4r::g3d::AnmObjTexPatRes* anmObj = nw4r::g3d::AnmObjTexPatRes::Construct(allocator, &instanceSize, anim, model, false);
            if (anmObj != NULL)
            {
                anmObj->Bind(model);

                if (modelAnim->m_anmObjTexPatRes != NULL)
                {
                    modelAnim->m_anmObjTexPatRes->Destroy();
                }

                modelAnim->m_anmObjTexPatRes = anmObj;
            }
        }
  //  }
}

inline void setTexPatAnim2(u8 animId,nw4r::g3d::ResMdl model, gfModelAnimation* modelAnim, Heaps::HeapType heap) {
    if (animId < modelAnim->m_resFile.GetResAnmTexPatNumEntries()) {
 //       int instanceSize;
        setTexPatAnim(animId,model, modelAnim,heap);
    }
}


inline void setTexSortAnim(u8 animId,nw4r::g3d::ResMdl model, gfModelAnimation* modelAnim, Heaps::HeapType heap) {
//    if (animId < modelAnim->m_resFile.GetResAnmClrNumEntries())
        int instanceSize;
        nw4r::g3d::ResAnmTexSrt anim = modelAnim->m_resFile.GetResAnmTexSrt((u32)animId);

        if (anim.IsValid())
        {
            MEMAllocator* allocator = gfHeapManager::getMEMAllocator(heap);
            nw4r::g3d::AnmObjTexSrtRes* anmObj = nw4r::g3d::AnmObjTexSrtRes::Construct(allocator, &instanceSize, anim, model, false);
            if (anmObj != NULL)
            {
                anmObj->Bind(model);

                if (modelAnim->m_anmObjTexSrtRes != NULL)
                {
                    modelAnim->m_anmObjTexSrtRes->Destroy();
                }

                modelAnim->m_anmObjTexSrtRes = anmObj;
            }
        }
  //  }
}

inline void setTexSortAnim2(u8 animId,nw4r::g3d::ResMdl model, gfModelAnimation* modelAnim, Heaps::HeapType heap) {
    if (animId < modelAnim->m_resFile.GetResAnmTexSrtNumEntries()) {
 //       int instanceSize;
        setTexSortAnim(animId,model, modelAnim,heap);
    }
}


inline void setColorAnim(u8 animId,nw4r::g3d::ResMdl model, gfModelAnimation* modelAnim, Heaps::HeapType heap) {
//    if (animId < modelAnim->m_resFile.GetResAnmClrNumEntries())
        int instanceSize;
        nw4r::g3d::ResAnmClr anim = modelAnim->m_resFile.GetResAnmClr((u32)animId);

        //MEMAllocator* allocator = gfHeapManager::getMEMAllocator(Heaps::StageInstance);
        if (anim.IsValid())
        {
            MEMAllocator* allocator = gfHeapManager::getMEMAllocator(heap);
            nw4r::g3d::AnmObjMatClrRes* anmObj = nw4r::g3d::AnmObjMatClrRes::Construct(allocator, &instanceSize, anim, model, false);
            if (anmObj != NULL)
            {
                anmObj->Bind(model);

                if (modelAnim->m_anmObjMatClrRes != NULL)
                {
                    modelAnim->m_anmObjMatClrRes->Destroy();
                }

                modelAnim->m_anmObjMatClrRes = anmObj;
            }
        }
  //  }
}

inline void setColorAnim2(u8 animId,nw4r::g3d::ResMdl model, gfModelAnimation* modelAnim, Heaps::HeapType heap) {
    if (animId < modelAnim->m_resFile.GetResAnmClrNumEntries()) {
 //       int instanceSize;
        setColorAnim(animId,model, modelAnim,heap);
    }
}