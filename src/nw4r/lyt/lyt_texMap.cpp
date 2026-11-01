#include <nw4r/lyt.h>

#include <revolution/GX.h>
#include <revolution/TPL.h>

namespace nw4r {
namespace lyt {

void TexMap::Get(GXTexObj* pTexObj) const {
    if (detail::IsCITexelFormat(GetTexelFormat())) {
        u32 tlut = GXGetTexObjTlut(pTexObj);

        GXInitTexObjCI(pTexObj, GetImage(), GetWidth(), GetHeight(),
                       GetTexelFormat(), GetWrapModeS(), GetWrapModeT(),
                       IsMipMap(), tlut);
    } else {
        GXInitTexObj(pTexObj, GetImage(), GetWidth(), GetHeight(),
                     GetTexelFormat(), GetWrapModeS(), GetWrapModeT(),
                     IsMipMap());
    }

    GXInitTexObjLOD(pTexObj, GetMinFilter(), GetMagFilter(), GetMinLOD(),
                    GetMaxLOD(), GetLODBias(), IsBiasClampEnable(),
                    IsEdgeLODEnable(), GetAnisotropy());
}

void TexMap::Get(GXTlutObj* pTlutObj) const {
    GXInitTlutObj(pTlutObj, GetPalette(), GetPaletteFormat(),
                  GetPaletteEntryNum());
}

void TexMap::Set(TPLPalette* pPalette, u32 id) {
    if (reinterpret_cast<u32>(pPalette->descriptors) < 0x80000000) {
        TPLBind(pPalette);
    }

    Set(TPLGet(pPalette, id));
}

void TexMap::Set(const TPLDescriptor* pDesc) {
    SetNoWrap(pDesc);

    const TPLHeader& rTexHeader = *pDesc->texHeader;
    SetWrapMode(rTexHeader.wrapS, rTexHeader.wrapT);
}

void TexMap::SetNoWrap(const TexMap& rOther) {
    GXTexWrapMode wrapS = GetWrapModeS();
    GXTexWrapMode wrapT = GetWrapModeT();

    Set(rOther);
    SetWrapMode(wrapS, wrapT);
}

void TexMap::SetNoWrap(const TPLDescriptor* pDesc) {
    const TPLHeader& rTexHeader = *pDesc->texHeader;

    SetImage(rTexHeader.data);
    SetSize(rTexHeader.width, rTexHeader.height);
    SetTexelFormat(static_cast<GXTexFmt>(rTexHeader.format));

    SetMipMap(rTexHeader.minLod != rTexHeader.maxLod);
    SetFilter(rTexHeader.minFilt, rTexHeader.magFilt);

    SetLOD(static_cast<f32>(rTexHeader.minLod),
           static_cast<f32>(rTexHeader.maxLod));

    SetLODBias(rTexHeader.lodBias);
    SetEdgeLODEnable(rTexHeader.edgeLodEnable);

    const TPLClutHeader* const pClutHeader = pDesc->clutHeader;

    if (pClutHeader != NULL) {
        SetPalette(pClutHeader->data);
        SetPaletteFormat(pClutHeader->format);
        SetPaletteEntryNum(pClutHeader->numEntries);
    } else {
        SetPalette(NULL);
        SetPaletteFormat(GX_TL_IA8);
        SetPaletteEntryNum(0);
    }
}

} // namespace lyt
} // namespace nw4r
