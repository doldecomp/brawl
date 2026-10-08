#ifndef NW4R_G3D_SCN_CHOICE_H
#define NW4R_G3D_SCN_CHOICE_H
#include <nw4r/types_nw4r.h>

#include <nw4r/g3d/g3d_scnobj.h>

namespace nw4r {
namespace g3d {

// Not part of the Wii Sports version of the library: a ScnGroup that only
// updates and draws one chosen child.
class ScnChoice : public ScnGroup {
public:
    static ScnChoice* Construct(MEMAllocator* pAllocator, u32* pSize,
                                int capacity);

    ScnChoice(MEMAllocator* pAllocator, ScnObj** ppObj, u32 capacity)
        : ScnGroup(pAllocator, ppObj, capacity), mpChoice(NULL) {}

    virtual void G3dProc(u32 task, u32 param, void* pInfo); // at 0xC
    virtual ~ScnChoice() {}                                 // at 0x10

    bool SetChoice(ScnObj* pObj);
    bool SetChoice(int idx);

    ScnObj* GetChoice() const {
        return mpChoice;
    }

private:
    // Drop the choice if it is no longer one of the children.
    void ValidateChoice();

private:
    ScnObj* mpChoice; // at 0xE8

    NW4R_G3D_RTTI_DECL_DERIVED(ScnChoice, ScnGroup);
};

} // namespace g3d
} // namespace nw4r

#endif
