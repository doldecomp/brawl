#pragma once

#include <ft/ft_common_data_accesser.h>
#include <types.h>

// Construction descriptors inferred from the article holder call sites.
struct ftRobotArticleKindInfo {
    s32 m_kind;
    s32 m_subKind;
    ftRobotArticleKindInfo() : m_kind(0), m_subKind(Fighter_Robot) { }
};
struct ftRobotArticleConstructionInfo {
    const ftRobotArticleKindInfo* m_kindInfo;
    void* m_heapModule;
    ftRobotArticleConstructionInfo(const ftRobotArticleKindInfo& kind, void* heap) :
        m_kindInfo(&kind), m_heapModule(heap) { }
};
