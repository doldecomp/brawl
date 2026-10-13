#pragma once

#include <StaticAssert.h>
#include <mt/mt_matrix.h>
#include <mt/mt_vector.h>
#include <so/model/so_model_module_simple.h>
#include <types.h>

class soModelNodeSetUp {
    // TODO data and functions
    u8 unk0[0x34];
};
static_assert(sizeof(soModelNodeSetUp) == 0x34, "Class is the wrong size!");

// TODO: name
struct UnkVirtualNodeInfo {
    u32 m_parentNodeId;
    Vec3f m_translate;
    Vec3f m_rotate;
};
static_assert(sizeof(UnkVirtualNodeInfo) == 0x1C, "Class is the wrong size!");

// Manages the SRT matrices for a set of model nodes with IDs ranging
// from m_start to m_end. TODO: This class likely has more inline methods
class soModelVirtualNode {
    u32 m_start;
    u32 m_end;
    UnkVirtualNodeInfo* m_nodeInfo;
    Matrix* m_matrices;
    bool m_unused;
public:
    soModelVirtualNode();
    ~soModelVirtualNode();
    void init(u32 start, u32 end, UnkVirtualNodeInfo* info, Matrix* mtxs);
    bool updateMatrix(const soModelModule& mod, u32 id, const Vec3f& scale);
    bool getMatrix(u32 id, Matrix& mtx) const;
    bool setMatrix(u32 id, Matrix& mtx);
    bool isNode(u32 id) const;
    bool getOffset(u32 id, Vec3f& offset) const;
    bool getNodeParent(u32 id, u32& parent) const;
};
static_assert(sizeof(soModelVirtualNode) == 0x14, "Class is the wrong size!");
