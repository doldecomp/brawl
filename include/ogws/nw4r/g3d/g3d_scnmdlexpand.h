#ifndef NW4R_G3D_SCN_MDL_EXPAND_H
#define NW4R_G3D_SCN_MDL_EXPAND_H
#include <nw4r/types_nw4r.h>

#include <nw4r/g3d/g3d_scnmdl.h>
#include <nw4r/g3d/g3d_scnobj.h>

namespace nw4r {
namespace g3d {

// Not part of the Wii Sports version of the library: a ScnGroup that owns a
// ScnMdl and attaches each of its children to a node of that model.
class ScnMdlExpand : public ScnGroup {
public:
    static ScnMdlExpand* Construct(MEMAllocator* pAllocator, u32* pSize,
                                   int capacity, ScnMdl* pScnMdl);

    ScnMdlExpand(MEMAllocator* pAllocator, ScnObj** ppObj, u32 capacity,
                 ScnMdl* pScnMdl, u32* pNodeID);

    virtual void G3dProc(u32 task, u32 param, void* pInfo); // at 0xC
    virtual ~ScnMdlExpand();                                // at 0x10

    virtual bool Insert(u32 idx, ScnObj* pObj); // at 0x34
    virtual ScnObj* Remove(u32 idx);            // at 0x38
    virtual bool Remove(ScnObj* pObj);          // at 0x3C

    bool PushBack(ScnObj* pObj, u32 nodeID);
    bool PushBack(ScnObj* pObj, const char* pNodeName);

private:
    bool SetNodeID(u32 idx, u32 nodeID);

private:
    ScnMdl* mpScnMdl; // at 0xE8
    u32* mpNodeID;    // at 0xEC

    NW4R_G3D_RTTI_DECL_DERIVED(ScnMdlExpand, ScnGroup);
};

} // namespace g3d
} // namespace nw4r

#endif
