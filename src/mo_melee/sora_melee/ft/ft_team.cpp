#include <ft/ft_manager.h>
#include <so/team/so_team_module_impl.h>
#include <types.h>

ftTeam::ftTeam(s32 entryId) : soTeam(false), m_entryId(entryId), m_teamNo(-1), m_2nd(-1) {
    reset();
}

void ftTeam::reset() {
    m_teamNo = g_ftManager->getTeam(m_entryId, true, true);
    m_2nd = g_ftManager->getTeam2nd(m_entryId);
}

s32 ftTeam::getNo() const {
    return m_teamNo;
}

s32 ftTeam::get2nd() const {
    return m_2nd;
}

s32 ftTeamIndirect::getNo() const {
    if (m_indirectTeamNo != -1)
        return m_indirectTeamNo;
    return m_teamNo;
}

void ftTeam::set2nd(s32 scnd) {
    m_2nd = scnd;
}

void ftTeam::setNo(s32 num) {
    m_teamNo = num;
}
