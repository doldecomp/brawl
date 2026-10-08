#include <st_fzero/gr_fzero.h>
#include <st_fzero/gr_fzero_anim.h>

inline grFzeroWall::grFzeroWall(const char* taskName) : grFzero(taskName) {
    m_sceneWork = NULL;
    m_stateWork = NULL;
    m_stateWallWork = NULL;
    m_mtxGimmickWork = NULL;
    m_animId = 1;
    m_animFrames = 0.0f;
}

grFzeroWall* grFzeroWall::create(int mdlIndex, const char* nodeName, const char* taskName) {
    grFzeroWall* ground = new (Heaps::StageInstance) grFzeroWall(taskName);
    if (ground != NULL) {
        ground->setMdlIndex(mdlIndex);
        ground->setTgtNode(nodeName);
    }
    return ground;
}

grFzeroWall::~grFzeroWall() {
}

void grFzeroWall::update(float deltaFrame) {
    grGimmick::update(deltaFrame);
    if (m_isUpdate) {
        updateActive(deltaFrame);
        updateG3dProcCalcWorld();
        m_hasUpdatedG3dCalcWorld = false;
        if (m_mtxGimmickWork != NULL) {
            getNodeMatrix(m_mtxGimmickWork + 39, 0, "wall_col_move");
        }
    }
}

// The wall is only there while its section's animation plays: it slides in when the course reaches section 2 and
// goes away again once the animation has run out.
void grFzeroWall::updateActive(float deltaFrame) {
    switch (m_state) {
    case 0:
        setMotion(1, 0, 1, 0);
        setVisibility(0);
        setEnableCollisionStatus(0);
        m_state = 1;
        break;
    case 1:
        if (*m_sceneWork == 2 && *m_stateWork == 0) {
            setMotion(0, 0, 1, &m_animFrames);
            setVisibility(1);
            setEnableCollisionStatus(1);
            *m_stateWallWork = 7;
            m_state = 3;
        }
        break;
    case 3:
        if (getMotionFrame(0) >= m_animFrames) {
            setMotion(1, 0, 1, 0);
            setVisibility(0);
            setEnableCollisionStatus(0);
            *m_stateWallWork = 8;
            m_state = 4;
        }
        break;
    case 4:
        if (*m_sceneWork != 2) {
            m_state = 1;
        }
        break;
    }
}

// Binds the single animation of the wall (animation 0); animation 1 means "none".
void grFzeroWall::setMotion(u32 animId, bool shouldLoop, bool force, float* frameCount) {
    if (m_animId == animId && force == 0) {
        return;
    }

    nw4r::g3d::ScnMdl* sceneMdl = *m_sceneModels;
    if (sceneMdl == NULL) {
        return;
    }

    gfModelAnimation* modelAnim = *m_modelAnims;
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
    m_animId = animId;

    if (animId >= 1) {
        return;
    }

    bool result = (modelAnim->m_resFile.GetResAnmChrNumEntries() > animId);
    if (result) {
        grFzeroSetChrAnim2(animId, model, modelAnim, Heaps::StageInstance);
    }

    result = (modelAnim->m_resFile.GetResAnmVisNumEntries() > animId);
    if (result) {
        grFzeroSetVisibilityAnim2(animId, model, modelAnim, Heaps::StageInstance);
    }

    result = (modelAnim->m_resFile.GetResAnmTexPatNumEntries() > animId);
    if (result) {
        grFzeroSetTexPatAnim2(animId, model, modelAnim, Heaps::StageInstance);
    }

    result = (modelAnim->m_resFile.GetResAnmTexSrtNumEntries() > animId);
    if (result) {
        grFzeroSetTexSrtAnim2(animId, model, modelAnim, Heaps::StageInstance);
    }

    result = (modelAnim->m_resFile.GetResAnmClrNumEntries() > animId);
    if (result) {
        grFzeroSetColorAnim2(animId, model, modelAnim, Heaps::StageInstance);
    }

    gfModelAnimation::bind(sceneMdl, modelAnim);
    modelAnim->setFrame(0.0);
    modelAnim->setUpdateRate(1.0);
    modelAnim->setLoop(shouldLoop);

    if (frameCount != NULL) {
        *frameCount = modelAnim->getFrameCount();
    }
}
