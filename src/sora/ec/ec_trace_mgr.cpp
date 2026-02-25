#include <ec/ec_mgr.h>
#include <ec/ec_trace.h>
#include <ec/ec_trace_mgr.h>
#include <ef/ef_id.h>
#include <mt/mt_vector.h>
#include <sr/sr_common.h>
#include <types.h>

ecTraceMgr::ecTraceMgr() : m_head(nullptr), m_nextId(0), m_length(0) { }

ecTraceMgr::~ecTraceMgr() {
    for (ecTrace* curr = m_head; curr; ) {
        ecTrace* node = curr;
        curr = curr->m_next;
        if (node)
            delete node;
    }
}

void ecTraceMgr::update_just() {
    ecTrace* curr = m_head;
    while (curr) {
        if (!curr->update_just()) {
            ecTrace* node = curr;
            curr = curr->m_next;
            if (node->m_prev)
                node->m_prev->m_next = node->m_next;
            else
                m_head = node->m_next;

            if (node->m_next)
                node->m_next->m_prev = node->m_prev;
            else
                m_tail = node->m_prev;

            m_length--;
            if (node)
                delete node;
            continue;
        }
        curr = curr->m_next;
    }
}

void ecTraceMgr::update_odd(float p1) {
    for (ecTrace* curr = m_head; curr; curr = curr->m_next)
        curr->update_odd(p1);
}

void ecTraceMgr::renderXlu() {
    for (ecTrace* curr = m_head; curr; curr = curr->m_next)
        curr->renderXlu();
}

u32 ecTraceMgr::start(u32 p1, u32 p2, u32 p3, u32 p4, u32 p5, u32 p6, u32 p7,
        u8 p8, u32 p9, float p10) {
    return regist(new (Heaps::Effect) ecTrace(p1, p2, p3, p4, p5, p7, p9), p6, p8, p10);
}

u32 ecTraceMgr::start(u32 p1, u32 p2, u32 p3, u32 p4, u32 p5, u32 p6, u8 p7,
        u32 p8, float p9) {
    return regist(new (Heaps::Effect) ecTrace(p1, p2, p3, p4, p6, p8), p5, p7, p9);
}

u32 ecTraceMgr::regist(ecTrace* trace, u32 p2, u8 p3, float p4) {
    if (!trace)
        return 0;
    if (g_ecMgr->unk90 != (p2 & g_ecMgr->unk94))
        return 0;

    if (++m_nextId == 0)
        ++m_nextId;
    trace->m_id = m_nextId;
    trace->unk28 = p2;

    switch (p3) {
        case 0:
            trace->unk64 = Vec3f(1.0f, 0.0f, 0.0f);
            break;
        case 1:
            trace->unk64 = Vec3f(0.0f, 1.0f, 0.0f);
            break;
        default:
            trace->unk64 = Vec3f(0.0f, 0.0f, 1.0f);
            break;
    }
    trace->unk74 = p4;
    if (!m_head) {
        m_tail = trace;
        m_head = trace;
        trace->m_next = nullptr;
        trace->m_prev = nullptr;
    } else {
        m_tail->m_next = trace;
        trace->m_prev = m_tail;
        trace->m_next = nullptr;
        m_tail = trace;
    }
    m_length++;
    return m_nextId;
}

bool ecTraceMgr::end(u32 id, u32 p2, u32 p3) {
    ecTrace* trace = getTraceById(id);
    if (!trace)
        return false;
    trace->end(p2, p3);
    return true;
}

void ecTraceMgr::endGroup(u32 p1, u32 p2, u32 p3) {
    ecTrace* curr = m_head;
    if (p1 & 0xFF000000)
        p2 |= 0xFF000000;
    p1 &= p2;
    for ( ; curr; curr = curr->m_next)
        if (p1 == (curr->unk28 & p2))
            curr->end(p3, 0);
}

void ecTraceMgr::pauseGroup(bool p1, u32 p2, u32 p3) {
    ecTrace* curr = m_head;
    if (p2 & 0xFF000000)
        p3 |= 0xFF000000;
    p2 &= p3;
    for ( ; curr; curr = curr->m_next)
        if (p2 == (curr->unk28 & p3))
            curr->pause(p1);
}

bool ecTraceMgr::setOffset(u32 id, const Vec3f& p2, const Vec3f& p3) {
    ecTrace* trace = getTraceById(id);
    if (!trace)
        return false;
    trace->unk4C = p2;
    trace->unk58 = p3;
    return true;
}

void ecTraceMgr::setAttachEffect(u32 id, EfID efId, nw4r::g3d::ScnMdl* scnMdl,
        const char* name, const Vec3f* pos, const Vec3f* rot, const Vec3f* scale) {
    ecTrace* trace = getTraceById(id);
    if (trace)
        switch (trace->unk2C) {
            case 0:
                trace->unk2C = g_ecMgr->setEffect(efId, pos, rot, scale);
                g_ecMgr->setParent2(trace->unk2C, scnMdl, name, 0);
                break;
            default:
                break;
        }
}
