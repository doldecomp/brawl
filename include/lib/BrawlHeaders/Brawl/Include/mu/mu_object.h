#pragma once

#include <StaticAssert.h>
#include <gf/gf_model.h>
#include <memory.h>
#include <nw4r/g3d/g3d_resfile.h>
#include <nw4r/g3d/g3d_resmdl.h>
#include <nw4r/g3d/g3d_scnobj.h>

class MuObject {

public:
    char unk[0x4];
    nw4r::g3d::ResFile m_resFile;
    nw4r::g3d::ResMdl m_resMdl;
    nw4r::g3d::ScnMdl* m_scnMdl;
    nw4r::g3d::ScnMdl* m_sceneModel;
    gfModelAnimation* m_modelAnim;
    char unk2[0x44];

    static MuObject* create(nw4r::g3d::ResFile* modelSource, const char* modelNode, int drawPriority, nw4r::g3d::ResFile* textureSource, HeapType type);
    static MuObject* create(nw4r::g3d::ResFile* modelSource, int modelNode, nw4r::g3d::ResFile* textureSource, int animNode, HeapType type);
    MuObject* copy(int modelNode, int animNode, HeapType type);

    void enableSkipMatrix(bool enableSkip);
    void enableSkipMaterial(bool enableSkip);
    void calcMatrix();

    void changeAnimN(const char* animName);
    void changeNodeAnimN(const char* animName);
    void changeClrAnimN(const char* animName);
    void changeVisAnimN(const char* animName);
    void changeTexPatAnimN(const char* animName);
    void changeTexSrtAnimN(const char* animName);

    void changeAnimNIf(const char* animName);
    void changeNodeAnimNIf(const char* animName);
    void changeClrAnimNIf(const char* animName);
    void changeVisAnimNIf(const char* animName);
    void changeTexPatAnimNIf(const char* animName);
    void changeTexSrtAnimNIf(const char* animName);

    void setFrame(float frame);
    void setFrameVisible(float frame);
    void setFrameMatCol(float frame);
    void setFrameTex(float frame);
    void setFrameTexSrt(float frame);
    void setFrameFlg(float frame, u8 flagFilter); // 1 CHR, 2 VIS, 4 PAT, 8 SRT, 10 CLR. SHP not supported
    void setFrameNode(float frame);
    void setUpdateRateFlg(float updateRate, u8 flagFilter);

    void changeMaterialTex(int matNode, int texNode, nw4r::g3d::ResFile* textureSource = nullptr);
    void changeMaterialTex(int matNode, const char* textureName, nw4r::g3d::ResFile* textureSource = nullptr);
    // void anmPlayPolicyOneTime(float, float, float);

    void getNode(int objNode);
    void getNodeID(const char* nodeName);
    void getRect3D(Rect2D* rectangle, int nodeA, int nodeB);
    void getRect3D(Rect2D* rectangle, const char* nodeNameA, const char* nodeNameB);

    void getPos(Vec3f* pos);
    void getPos(Vec3f* pos, const char* nodeName);
    void setPos(Vec3f* pos);
    void setPos(Vec3f* pos, const char* nodeName);
    void setTrans(Vec3f* trans);

    // Vec3f getGlobalPostiion(int resNode); //Ambiguous with below?
    Vec3f getGlobalPosition(int resNode);
    Vec3f getGlobalPosition();

    void getAnimScale(Vec3f* scl, const char* name);
    void setScale(Vec3f* scl);
    void setScale(const char* name, Vec3f* scl);
    void getScale(Vec3f* scl, const char* name);
    void setObjScale(Vec3f* scl);
    Vec3f getObjScale();

    void setObjRotate(Vec3f* rot);
    void getRotate(Vec3f* rot, const char* name);
    void setRotate(Vec3f* rot, const char* name);

    const char* getNodeAnimName();
    const char* getVisAnimName();
    const char* getTexPatAnimName();
    const char* getTexSrtAnimName();
    const char* getClrAnimName();

    int isNodeAnimFinished();
    int isVisAnimFinished();
    int isClrAnimFinished();
    int isAnimFinished();
    bool isNodeAnimLoop();

    virtual ~MuObject();
};
static_assert(sizeof(MuObject) == 0x60, "Class is wrong size!");

class muObjProcessTask {
public:
    char unk[0x44];

    static muObjProcessTask* create(HeapType type);
    virtual ~muObjProcessTask();
};
static_assert(sizeof(muObjProcessTask) == 0x48, "Class is wrong size!");
