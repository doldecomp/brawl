#pragma once

#include <StaticAssert.h>
#include <gr/collision/gr_collision_handle.h>
#include <gr/collision/gr_collision_linework.h>
#include <nw4r/ut/ut_LinkList.h>
#include <types.h>

class Stage;

class grCollision {
public:
    // 0
    short m_index;
    // 2
    short m_vtxLen;
    // 4
    short m_lineLen;
    // 6
    short m_jointLen;
    // 8
    grCollData* m_collData;
    // 12
    grCollData::VtxData* m_vtxDatas;
    // 16
    Vec2f* m_vtxPositions;
    // 20
    grCollisionLine* m_lines;
    // 24
    grCollisionJoint* m_joints;
    // 28
    clAABBox2D m_aabBox;
    // 44
    char _spacer[4];
    // 48
    void* m_next;
    // 52
    void* m_prev;
    // TOTAL_SIZE == 56
public:
    static grCollision* create(Stage* stage, void* colData, Ground* ground, int unk2);
    grCollision(void* colData, int unk1, int unk2);
    ~grCollision();

    grCollisionJoint* getJoint(u16 nodeIndex);
    grCollisionLine* getLine(u16 index);
    void getSegment(clSegment2D* outSegment, grCollisionLine* line);


};
static_assert(sizeof(grCollision) == 56, "Class is wrong size!");

// TODO: magic number 52 could be the size of a class
struct grCollisionList : public nw4r::ut::LinkList<grCollisionHandle, 52> {

};
// TODO size assertion

extern grCollisionList g_grCollisionList;
