#include <mt/mt_matrix.h>
#include <mt/mt_vector.h>
#include <so/model/so_model_module_simple.h>
#include <so/model/so_model_virtual_node.h>
#include <types.h>

// Same logic as isNode, but inlining the function call doesn't match
#define IF_VALID_NODE_ID(ID, CODE)                      \
    if (!m_nodeInfo)                                    \
        return false;                                   \
    if ((ID) >= m_start && (ID) < (m_start + m_end)) {  \
        CODE                                            \
        return true;                                    \
    }                                                   \
    return false;

soModelVirtualNode::soModelVirtualNode() :
    m_start(0),
    m_end(0),
    m_nodeInfo(nullptr),
    m_matrices(nullptr),
    m_unused(true) { }

soModelVirtualNode::~soModelVirtualNode() { }

void soModelVirtualNode::init(u32 start, u32 end, UnkVirtualNodeInfo* info, Matrix* mtxs) {
    m_start = start;
    m_end = end;
    m_nodeInfo = info;
    m_matrices = mtxs;
}

bool soModelVirtualNode::updateMatrix(const soModelModule& mod, u32 id, const Vec3f& scale) {
    IF_VALID_NODE_ID(id,
        u32 idx = id - m_start;
        mod.getNodeGlobalMtx(m_nodeInfo[idx].m_parentNodeId, &m_matrices[idx], true);
        Vec3f rot;
        Vec3f xlate;
        Matrix srt(true);
        xlate = m_nodeInfo[idx].m_translate;
        rot = m_nodeInfo[idx].m_rotate;
        srt.setSRT(scale, rot, xlate);
        m_matrices[idx].mul(&srt, &m_matrices[idx]);
    )
}

bool soModelVirtualNode::getMatrix(u32 id, Matrix& mtx) const {
    IF_VALID_NODE_ID(id,
        mtx = m_matrices[id - m_start];
    )
}

bool soModelVirtualNode::setMatrix(u32 id, Matrix& mtx) {
    IF_VALID_NODE_ID(id,
        m_matrices[id - m_start] = mtx;
    )
}

bool soModelVirtualNode::isNode(u32 id) const {
    IF_VALID_NODE_ID(id, /* nothing */)
}

bool soModelVirtualNode::getOffset(u32 id, Vec3f& offset) const {
    IF_VALID_NODE_ID(id,
        offset = m_nodeInfo[id - m_start].m_translate;
    )
}

bool soModelVirtualNode::getNodeParent(u32 id, u32& parent) const {
    IF_VALID_NODE_ID(id,
        parent = m_nodeInfo[id - m_start].m_parentNodeId;
    )
}
