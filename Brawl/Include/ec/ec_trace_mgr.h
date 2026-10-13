#pragma once

#include <ec/ec_trace.h>
#include <ef/ef_id.h>
#include <mt/mt_vector.h>
#include <nw4r/g3d/g3d_scnmdl.h>
#include <types.h>

struct ecTraceMgr {
    ecTrace* m_head;
    ecTrace* m_tail;
    u32 m_nextId;
    u32 m_length;

    ecTraceMgr();
    ~ecTraceMgr();
    void update_just();
    void update_odd(float p1);
    void renderXlu();

    u32 start(u32 p1, u32 p2, u32 p3, u32 p4, u32 p5, u32 p6, u32 p7, u8 p8,
        u32 p9, float p10);
    u32 start(u32 p1, u32 p2, u32 p3, u32 p4, u32 p5, u32 p6, u8 p7, u32 p8,
        float p9);
    u32 regist(ecTrace* trace, u32 p2, u8 p3, float p4);
    bool end(u32 id, u32 p2, u32 p3);
    void endGroup(u32 p1, u32 p2, u32 p3);
    void pauseGroup(bool p1, u32 p2, u32 p3);
    bool setOffset(u32 id, const Vec3f& p2, const Vec3f& p3);
    void setAttachEffect(u32 id, EfID efId, nw4r::g3d::ScnMdl* scnMdl, u32 nodeIndex,
        const Vec3f* pos, const Vec3f* rot, const Vec3f* scale);

    ecTrace* getTraceById(u32 id) const {
        if (id)
            for (ecTrace* curr = m_head; curr; curr = curr->m_next)
                if (curr->m_id == id)
                    return curr;
        return nullptr;
    }
};
// TODO size
