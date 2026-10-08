#include <mt/mt_prng.h>
#include <so/work/so_work_manage_module_impl.h>

// A work variable ID packs which general work holds it (top nibble) and the variable number (low 24 bits).
// Flag IDs address a single bit: the low 8 bits are the bit number, 32 bits to a word.
#define WORK_OF(index) m_generalWorks[(index) >> 28]
#define WORK_VAR(index) ((index) & 0xFFFFFF)

// Clears every general work and releases the lock counters.
void soWorkManageModuleImpl::activate() {
    for (int i = 0; i < 3; i++) {
        if (m_generalWorks[i] != NULL)
            m_generalWorks[i]->clearWorkAll();
    }
    soLockable::reset();
}

void soWorkManageModuleImpl::setWork(u32 index, soGeneralWorkAbstract* generalWork) {
    m_generalWorks[index] = generalWork;
}

int soWorkManageModuleImpl::getInt(u32 index) {
    return WORK_OF(index)->getIntWork(WORK_VAR(index));
}

void soWorkManageModuleImpl::setInt(int value, u32 index) {
    WORK_OF(index)->setIntWork(value, WORK_VAR(index));
}

// Sets the variable to a random value in [minValue, maxValue]; does nothing for an empty range.
void soWorkManageModuleImpl::rndInt(int minValue, int maxValue, u32 index) {
    if (maxValue < minValue)
        return;
    int value;
    if (maxValue == minValue)
        value = maxValue;
    else
        value = minValue + randi(maxValue - minValue + 1);
    setInt(value, index);
}

void soWorkManageModuleImpl::incInt(u32 index) {
    WORK_OF(index)->incIntWork(WORK_VAR(index));
}

void soWorkManageModuleImpl::decInt(u32 index) {
    WORK_OF(index)->decIntWork(WORK_VAR(index));
}

void soWorkManageModuleImpl::addInt(int addValue, u32 index) {
    WORK_OF(index)->addIntWork(addValue, WORK_VAR(index));
}

void soWorkManageModuleImpl::subInt(int subtractValue, u32 index) {
    WORK_OF(index)->subIntWork(subtractValue, WORK_VAR(index));
}

// Counts the variable down by one while it is above the threshold; true on the step that reaches the threshold.
u32 soWorkManageModuleImpl::countDownInt(u32 index, int threshold) {
    int value = getInt(index);
    if (value > threshold) {
        setInt(value - 1, index);
        return value - 1 == threshold;
    }
    return 0;
}

float soWorkManageModuleImpl::getFloat(u32 index) {
    return WORK_OF(index)->getFloatWork(WORK_VAR(index));
}

void soWorkManageModuleImpl::setFloat(float value, u32 index) {
    WORK_OF(index)->setFloatWork(value, WORK_VAR(index));
}

// Sets the variable to a random value in [minValue, maxValue]; does nothing for an empty range.
void soWorkManageModuleImpl::rndFloat(float minValue, float maxValue, u32 index) {
    if (maxValue < minValue)
        return;
    float value;
    if (maxValue == minValue)
        value = maxValue;
    else
        value = minValue + (1.17549435e-38f + (maxValue - minValue)) * randf();
    setFloat(value, index);
}

void soWorkManageModuleImpl::addFloat(float addValue, u32 index) {
    WORK_OF(index)->addFloatWork(addValue, WORK_VAR(index));
}

void soWorkManageModuleImpl::subFloat(float subtractValue, u32 index) {
    WORK_OF(index)->subFloatWork(subtractValue, WORK_VAR(index));
}

bool soWorkManageModuleImpl::isFlag(u32 index) {
    return WORK_OF(index)->isFlag(1 << (index & 0x1F), (int)(index & 0xFF) / 32);
}

void soWorkManageModuleImpl::onFlag(u32 index) {
    WORK_OF(index)->onFlag(1 << (index & 0x1F), (int)(index & 0xFF) / 32);
}

void soWorkManageModuleImpl::offFlag(u32 index) {
    WORK_OF(index)->offFlag(1 << (index & 0x1F), (int)(index & 0xFF) / 32);
}

u32 soWorkManageModuleImpl::turnOffFlag(u32 index) {
    return WORK_OF(index)->turnOffFlag(1 << (index & 0x1F), (int)(index & 0xFF) / 32);
}

void soWorkManageModuleImpl::clearAll(u32 index) {
    m_generalWorks[index]->clearWorkAll();
}

// The module listens for anim cmd type 0x12 (work variable commands).
bool soWorkManageModuleImpl::isObserv(char kind) {
    return kind == 0x12;
}

void* soWorkManageModuleImpl::getParamAccesser() {
    return m_paramAccesser;
}

void soWorkManageModuleImpl::setFlag(bool on, u32 index) {
    if (on == true)
        onFlag(index);
    else
        offFlag(index);
}
