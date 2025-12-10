#include <StaticAssert.h>
#include <gr/gr_path.h>
#include <types.h>

typedef grFixedPath::UnkClass UnkClass;

void grFixedPathCollection::relocation() {
    UnkClass* data;
    u32 offset = 0;
    const u32 count = m_count;

    m_paths = m_pathData;
    data = reinterpret_cast<UnkClass*>(m_paths + m_count);
    for (u32 i = 0; i != count; i++) {
        grFixedPath* p = &m_paths[i];
        p->m_data = data + offset;
        offset += p->m_offsetToNextEntry;
    }
}
