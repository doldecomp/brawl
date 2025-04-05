#include <gf/gf_3d_scene_event.h>
#include <types.h>

gfSceneRootEventList::~gfSceneRootEventList() { }

void gfSceneRootEventList::notify(s32 p1) {
    gfSceneRootEvent* node = head;
    while (node) {
        node->notify(p1);
        node = static_cast<gfSceneRootEvent*>(node->m_next);
    }
}
