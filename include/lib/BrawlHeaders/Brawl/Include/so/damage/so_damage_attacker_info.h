#pragma once

#include <StaticAssert.h>
#include <so/so_kind.h>
#include <gf/gf_task.h>
#include <types.h>

class soDamageAttackerInfo {
public:
    gfTask::Category m_directTaskCategory : 8;
    char _spacer[3];
    int m_directTaskId;
    soKind m_directSoKind;
    int m_directSoSubKind;

    gfTask::Category m_indirectTaskCategory : 8;
    char _spacer2[3];
    int m_indirectTaskId;
    soKind m_indirectSoKind;
    int m_indirectSoSubKind;
    int m_indirectEntryId;

    int m_clearFrame;
};
static_assert(sizeof(soDamageAttackerInfo) == 40, "Class is wrong size!");
