#pragma once

#include <StaticAssert.h>
#include <types.h>
#include <so/camera/so_camera_subject.h>
#include <so/anim/so_anim_cmd_event_presenter.h>

class soModuleAccesser;

class soCameraModule {
public:
    enum QuakeKind {
        Quake_None = -1,
        Quake_S = 0,
        Quake_Small = 0,
        Quake_L = 1,
        Quake_Large = 1,
        Quake_XL = 2,
        Quake_More_Large = 2,
        Quake_M = 3,
        Quake_Middle = 3,
        Quake_S_Half = 4,
        Quake_Small_Hf = 4,
    };

    virtual ~soCameraModule();
    virtual u32 getSubjectsSize();
    virtual void setup();
    virtual void setup(soSet<soCameraRange>* cameraRangeSet);
    virtual void setTrainingRangeData(soCameraRange*, u32 index);
    virtual void setZoomParam(soCameraZoom*, u32 index);
    virtual void activate();
    virtual void deactivate();
    virtual void resetAll();
    virtual void update();
    virtual void updateForce(u32 index, Vec3f*, Vec3f*);
    virtual void setWhole(bool);
    virtual void setEnableCamera(bool, int index);
    virtual void setEnableUpdatePos(bool, int index);
    virtual void setEnableInterpolatePos(bool, int index);
    virtual soCameraRange* getCameraRangeData(u32 index);
    virtual void resetCameraRange(u32 index);
    virtual void addCameraRangeOffset(Vec3f* offset, u32 index);
    virtual void addCameraRangeRect(Rect2D* rect, u32 index);
    virtual void addCameraZoom(float zoom, u32 index);
    virtual void unRegistCamera(u32 index);
    virtual void zoomIn(short, u32 index, Vec2f*, float);
    virtual void zoomOut();
    virtual void renderDebug();
    virtual void setQuake(bool);
    virtual void reqQuake(QuakeKind, soModuleAccesser*);
    virtual void reqQuake(QuakeKind, Vec3f* pos);
    virtual void stopQuake(QuakeKind);
    virtual QuakeKind getQuakeKind();
    virtual Vec3f getMainCameraTargetPos();
    virtual void setPri(u8 pri, int index);
    virtual u8 getPri(u32 index);
    virtual void setAdvPri(u8 pri, int index);
    virtual u8 getAdvPri(u32 index);
    virtual void setPlayerNo(u8 playerNo, int index);
    virtual u8 getPlayerNo(u32 index);
    virtual void setDemoDistScaleMul(float, u32 index);
    virtual void setDamage(short damage, u32 index);
    virtual void setDamageFly(u32 index);
    virtual void exitDamageFly(u32 index);
    virtual void setRun(u32 index);
    virtual void exitRun(u32 index);
    virtual bool isLocked();
    virtual bool isClipIn(bool);
    virtual bool isClipInAll(bool);
    virtual s8 getClipOutStatus(bool);
    virtual soCameraClipSphere* getClipSphere(u32 index);
    virtual void getSubjectRange(Rect2D* outRange, u32 index);
    virtual Vec3f getSubjectPos(u32 index);
    virtual float getSubjectOffsetY(u32 index);
    virtual soCameraSubject* getSubject(u32 index);
    virtual void getCameraRangeGlobalRect(Rect2D* outRange, u32 index);
    virtual void setCameraRangeGlobalRect(Rect2D* range, soModuleAccesser* moduleAccesser, u32 index);
    virtual void setOffsetGlobalRectCenter(Rect2D* range, soModuleAccesser* moduleAccesser, u32 index);
};


class soCameraModuleSimple : public soCameraModule, public soAnimCmdEventObserver {
    soModuleAccesser* m_moduleAccesser;
    u8 _0x14;
    char _0x15[3];
public:
    virtual ~soCameraModuleSimple();
    virtual u32 getSubjectsSize();
    virtual void setup();
    virtual void setup(soSet<soCameraRange>* cameraRangeSet);
    virtual void setTrainingRangeData(soCameraRange*, u32 index);
    virtual void setZoomParam(soCameraZoom*, u32 index);
    virtual void activate();
    virtual void deactivate();
    virtual void resetAll();
    virtual void update();
    virtual void updateForce(u32 index, Vec3f*, Vec3f*);
    virtual void setWhole(bool);
    virtual void setEnableCamera(bool, int index);
    virtual void setEnableUpdatePos(bool, int index);
    virtual void setEnableInterpolatePos(bool, int index);
    virtual soCameraRange* getCameraRangeData(u32 index);
    virtual void resetCameraRange(u32 index);
    virtual void addCameraRangeOffset(Vec3f* offset, u32 index);
    virtual void addCameraRangeRect(Rect2D* rect, u32 index);
    virtual void addCameraZoom(float zoom, u32 index);
    virtual void unRegistCamera(u32 index);
    virtual void zoomIn(short, u32 index, Vec2f*, float);
    virtual void zoomOut();
    virtual void renderDebug();
    virtual void setQuake(bool);
    virtual void reqQuake(QuakeKind, soModuleAccesser*);
    virtual void reqQuake(QuakeKind, Vec3f* pos);
    virtual void stopQuake(QuakeKind);
    virtual QuakeKind getQuakeKind();
    virtual Vec3f getMainCameraTargetPos();
    virtual void setPri(u8 pri, int index);
    virtual u8 getPri(u32 index);
    virtual void setAdvPri(u8 pri, int index);
    virtual u8 getAdvPri(u32 index);
    virtual void setPlayerNo(u8 playerNo, int index);
    virtual u8 getPlayerNo(u32 index);
    virtual void setDemoDistScaleMul(float, u32 index);
    virtual void setDamage(short damage, u32 index);
    virtual void setDamageFly(u32 index);
    virtual void exitDamageFly(u32 index);
    virtual void setRun(u32 index);
    virtual void exitRun(u32 index);
    virtual bool isLocked();
    virtual bool isClipIn(bool);
    virtual bool isClipInAll(bool);
    virtual s8 getClipOutStatus(bool);
    virtual soCameraClipSphere* getClipSphere(u32 index);
    virtual void getSubjectRange(Rect2D* outRange, u32 index);
    virtual Vec3f getSubjectPos(u32 index);
    virtual float getSubjectOffsetY(u32 index);
    virtual soCameraSubject* getSubject(u32 index);
    virtual void getCameraRangeGlobalRect(Rect2D* outRange, u32 index);
    virtual void setCameraRangeGlobalRect(Rect2D* range, soModuleAccesser* moduleAccesser, u32 index);
    virtual void setOffsetGlobalRectCenter(Rect2D* range, soModuleAccesser* moduleAccesser, u32 index);

    virtual bool isObserv(char unk1);
    virtual bool notifyEventAnimCmd(acAnimCmd* acmd, soModuleAccesser* moduleAccesser, int unk3);
};
static_assert(sizeof(soCameraModuleSimple) == 0x18, "Class is wrong size!");