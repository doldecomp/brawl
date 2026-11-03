#ifndef RVL_SDK_MTX_MTX_H
#define RVL_SDK_MTX_MTX_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef f32 Mtx[3][4];
typedef f32 Mtx44[4][4];

#define MTXDegToRad(a) ((a) * 0.01745329252f)

typedef struct Vec {
    f32 x, y, z;
} Vec;

typedef Vec Point3d;

typedef struct Quaternion {
    f32 x, y, z, w;
} Quaternion;

void PSMTXIdentity(Mtx);
void PSMTXCopy(const Mtx, Mtx);
void PSMTXConcat(const Mtx, const Mtx, Mtx);
void PSMTXConcatArray(const Mtx, const Mtx, Mtx, u32);
void PSMTXTranspose(const Mtx, Mtx);
u32 PSMTXInverse(const Mtx, Mtx);
u32 PSMTXInvXpose(const Mtx, Mtx);
void PSMTXRotRad(Mtx, char, f32);
void PSMTXRotTrig(Mtx, char, f32, f32);
void PSMTXRotAxisRad(Mtx, const Vec*, f32);
void PSMTXTrans(Mtx, f32, f32, f32);
void PSMTXTransApply(const Mtx, Mtx, f32, f32, f32);
void PSMTXScale(Mtx, f32, f32, f32);
void PSMTXScaleApply(const Mtx, Mtx, f32, f32, f32);
void PSMTXQuat(Mtx, const Quaternion*);

void C_MTXLookAt(Mtx, const Point3d*, const Vec*, const Point3d*);
void C_MTXLightFrustum(Mtx, f32, f32, f32, f32, f32, f32, f32, f32, f32);
void C_MTXLightPerspective(Mtx, f32, f32, f32, f32, f32, f32);
void C_MTXLightOrtho(Mtx, f32, f32, f32, f32, f32, f32, f32, f32);

#ifdef __cplusplus
}
#endif
#endif
