#pragma once

#include <StaticAssert.h>
#include <types.h>
#include <ut/ut_uncopyable.h>
#include <so/so_array.h>

class stEnemyIdManager : public utUnCopyable {
    soArrayList<u32, 32> m_enemyIdArrayList;
    u32 m_maxNumEnemmies;
    u32 m_numEnemies;
public:
    virtual ~stEnemyIdManager();

    inline bool addEnemyId(u32 createId) {
        if (!isFull()) {
            m_enemyIdArrayList.push(createId);
            m_numEnemies++;
            return true;
        }
        return false;
    }

    inline bool removeEnemyId(u32 createId) {
        for (u32 i = 0; i < getNumEnemies(); i++) {
            if (createId == getEnemyId(i)) {
                m_enemyIdArrayList.erase(i);
                m_numEnemies--;
                return true;
            }
        }
        return false;
    }

    inline void removeAll() {
        m_enemyIdArrayList.clear();
        m_numEnemies = 0;
    }

    inline u32 getEnemyId(u32 index) {
        return m_enemyIdArrayList.at(index);
    }

    inline u32 getNumEnemies() {
        return m_numEnemies;
    }

    inline bool isFull() {
        return getNumEnemies() >= m_maxNumEnemmies;
    }

    static void create();
    static void remove();

};
static_assert(sizeof(stEnemyIdManager) == 0x194, "Class is wrong size!");

extern stEnemyIdManager* g_stEnemyIdManager;
