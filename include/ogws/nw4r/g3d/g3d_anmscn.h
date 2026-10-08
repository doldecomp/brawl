#ifndef NW4R_G3D_ANM_SCN_H
#define NW4R_G3D_ANM_SCN_H
#include <nw4r/types_nw4r.h>

#include <nw4r/g3d/g3d_anmobj.h>
#include <nw4r/g3d/g3d_camera.h>
#include <nw4r/g3d/g3d_fog.h>
#include <nw4r/g3d/g3d_light.h>
#include <nw4r/g3d/g3d_obj.h>
#include <nw4r/g3d/res/g3d_resanmscn.h>
#include <nw4r/g3d/res/g3d_resanmamblight.h>
#include <nw4r/g3d/res/g3d_resanmlight.h>
#include <nw4r/g3d/res/g3d_resanmfog.h>
#include <nw4r/g3d/res/g3d_resanmcamera.h>

namespace nw4r {
namespace g3d {

// Forward declarations
struct AmbLightAnmResult;
class AnmScnRes;
struct CameraAnmResult;
struct FogAnmResult;
struct LightAnmResult;
class LightSetting;

class AnmScn : public G3dObj {
public:
    explicit AnmScn(MEMAllocator* pAllocator) : G3dObj(pAllocator, NULL) {}
    virtual ~AnmScn(); // at 0x10

    virtual void SetFrame(f32 frame) = 0; // at 0x1C
    virtual f32 GetFrame() const = 0;     // at 0x20

    virtual void SetUpdateRate(f32 rate) = 0; // at 0x24
    virtual f32 GetUpdateRate() const = 0;    // at 0x28
    virtual void UpdateFrame() = 0;           // at 0x2C

    virtual AnmScnRes* Attach(int idx, AnmScnRes* pRes); // at 0x30
    virtual AnmScnRes* Detach(int idx);                  // at 0x34

    virtual u32 GetNumLightSet() const = 0;      // at 0x38
    virtual u32 GetNumAmbLight() const = 0;      // at 0x3C
    virtual u32 GetNumDiffuseLight() const = 0;  // at 0x40
    virtual u32 GetNumSpecularLight() const = 0; // at 0x44
    virtual u32 GetNumFog() const = 0;           // at 0x48
    virtual u32 GetNumCamera() const = 0;        // at 0x4C

    virtual u32 GetLightSetMaxRefNumber() const = 0;     // at 0x50
    virtual u32 GetAmbLightMaxRefNumber() const = 0;     // at 0x54
    virtual u32 GetDiffuseLightMaxRefNumber() const = 0; // at 0x58
    virtual u32 GetFogMaxRefNumber() const = 0;          // at 0x5C
    virtual u32 GetCameraMaxRefNumber() const = 0;       // at 0x60

    virtual bool GetLightSet(LightSet set, u32 refNumber) = 0; // at 0x64
    virtual ut::Color GetAmbLightColor(u32 refNumber) = 0;     // at 0x68
    virtual void GetLight(LightObj* pDiff, LightObj* pSpec,
                          u32 refNumber) = 0;                 // at 0x6C
    virtual void GetFog(Fog fog, u32 refNumber) = 0;          // at 0x70
    virtual bool GetCamera(Camera camera, u32 refNumber) = 0; // at 0x74

    virtual u32 GetSpecularLightID(u32 refNumber) const = 0; // at 0x78
    virtual bool HasSpecularLight(u32 refNumber) const = 0;  // at 0x7C

    virtual AmbLightAnmResult* GetAmbLightResult(AmbLightAnmResult* pResult,
                                                 u32 refNumber) = 0; // at 0x80
    virtual LightAnmResult* GetLightResult(LightAnmResult* pResult,
                                           u32 refNumber) = 0; // at 0x84
    virtual FogAnmResult* GetFogResult(FogAnmResult* pResult,
                                       u32 refNumber) = 0; // at 0x88
    virtual CameraAnmResult* GetCameraResult(CameraAnmResult* pResult,
                                             u32 refNumber) = 0; // at 0x8C

    void GetLightSetting(LightSetting* pSetting);

private:
    NW4R_G3D_RTTI_DECL_DERIVED(AnmScn, G3dObj);
};

/******************************************************************************
 *
 * AnmScnRes
 *
 ******************************************************************************/
// NOTE: the layout (members after FrameCtrl) was recovered from this binary.
class AnmScnRes : public AnmScn, protected FrameCtrl {
public:
    static AnmScnRes* Construct(MEMAllocator* pAllocator, u32* pSize,
                                ResAnmScn scn, bool cache);

    AnmScnRes(MEMAllocator* pAllocator, ResAnmScn scn,
              AmbLightAnmResult* pAmbLightCache, LightAnmResult* pLightCache,
              FogAnmResult* pFogCache, CameraAnmResult* pCameraCache);

    virtual void G3dProc(u32 task, u32 param, void* pInfo); // at 0xC
    virtual ~AnmScnRes();                                   // at 0x10

    virtual void SetFrame(f32 frame); // at 0x1C
    virtual f32 GetFrame() const;     // at 0x20

    virtual void SetUpdateRate(f32 rate); // at 0x24
    virtual f32 GetUpdateRate() const;    // at 0x28
    virtual void UpdateFrame();           // at 0x2C

    virtual u32 GetNumLightSet() const;      // at 0x38
    virtual u32 GetNumAmbLight() const;      // at 0x3C
    virtual u32 GetNumDiffuseLight() const;  // at 0x40
    virtual u32 GetNumSpecularLight() const; // at 0x44
    virtual u32 GetNumFog() const;           // at 0x48
    virtual u32 GetNumCamera() const {       // at 0x4C
        return mRes.GetResAnmCameraNumEntries();
    }

    virtual u32 GetLightSetMaxRefNumber() const { // at 0x50
        return mRes.GetResLightSetMaxRefNumber();
    }
    virtual u32 GetAmbLightMaxRefNumber() const;  // at 0x54
    virtual u32 GetDiffuseLightMaxRefNumber() const { // at 0x58
        return mRes.GetResAnmLightMaxRefNumber();
    }
    virtual u32 GetFogMaxRefNumber() const;    // at 0x5C
    virtual u32 GetCameraMaxRefNumber() const; // at 0x60

    virtual bool GetLightSet(LightSet set, u32 refNumber); // at 0x64
    virtual ut::Color GetAmbLightColor(u32 refNumber);     // at 0x68
    virtual void GetLight(LightObj* pDiff, LightObj* pSpec,
                          u32 refNumber);                 // at 0x6C
    virtual void GetFog(Fog fog, u32 refNumber);          // at 0x70
    virtual bool GetCamera(Camera camera, u32 refNumber); // at 0x74

    virtual u32 GetSpecularLightID(u32 refNumber) const; // at 0x78
    virtual bool HasSpecularLight(u32 refNumber) const;  // at 0x7C

    virtual AmbLightAnmResult* GetAmbLightResult(AmbLightAnmResult* pResult,
                                                 u32 refNumber); // at 0x80
    virtual LightAnmResult* GetLightResult(LightAnmResult* pResult,
                                           u32 refNumber); // at 0x84
    virtual FogAnmResult* GetFogResult(FogAnmResult* pResult,
                                       u32 refNumber); // at 0x88
    virtual CameraAnmResult* GetCameraResult(CameraAnmResult* pResult,
                                             u32 refNumber); // at 0x8C

private:
    enum Flag { FLAG_USE_CACHE = (1 << 0) };

    void UpdateCache();

private:
    ResAnmScn mRes;                    // at 0x20
    u32 mFlags;                        // at 0x24
    AmbLightAnmResult* mpAmbLightCache; // at 0x28
    LightAnmResult* mpLightCache;      // at 0x2C
    FogAnmResult* mpFogCache;          // at 0x30
    CameraAnmResult* mpCameraCache;    // at 0x34

    NW4R_G3D_RTTI_DECL_DERIVED(AnmScnRes, AnmScn);
};

} // namespace g3d
} // namespace nw4r

#endif
