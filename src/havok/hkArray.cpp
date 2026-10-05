#include <havok/hkArray.h>
#include <havok/hkString.h>

void hkArrayUtil::_reserve(hkArrayBase* array, int newCapacity, int elemSize) {
    void* newData = hkThreadMemory::s_instance->allocateChunk(newCapacity * elemSize, 0x15);
    hkString::memCpy(newData, array->m_data, array->m_size * elemSize);
    if (!(array->m_capacityAndFlags & hkArrayBase::DONT_DEALLOCATE_FLAG)) {
        hkThreadMemory::s_instance->deallocateChunk(
            array->m_data, elemSize * (array->m_capacityAndFlags & hkArrayBase::CAPACITY_MASK), 0x15);
    }
    array->m_data = newData;
    array->m_capacityAndFlags =
        newCapacity | (array->m_capacityAndFlags & hkArrayBase::FORCE_SIGN_FLAG);
}

void hkArrayUtil::_reserveMore(hkArrayBase* array, int elemSize) {
    int newCapacity = 1;
    if (array->m_size != 0) {
        newCapacity = array->m_size * 2;
    }
    void* newData = hkThreadMemory::s_instance->allocateChunk(newCapacity * elemSize, 0x15);
    hkString::memCpy(newData, array->m_data, array->m_size * elemSize);
    if (!(array->m_capacityAndFlags & hkArrayBase::DONT_DEALLOCATE_FLAG)) {
        hkThreadMemory::s_instance->deallocateChunk(
            array->m_data, elemSize * (array->m_capacityAndFlags & hkArrayBase::CAPACITY_MASK), 0x15);
    }
    array->m_data = newData;
    array->m_capacityAndFlags =
        newCapacity | (array->m_capacityAndFlags & hkArrayBase::FORCE_SIGN_FLAG);
}

void hkArrayUtil::_reduce(hkArrayBase* array, int elemSize, void* buffer, int bufferCapacity) {
    int newCapacity;
    int flags;
    void* newData;
    if (buffer != 0 && array->m_size < bufferCapacity) {
        newData = buffer;
        newCapacity = bufferCapacity;
        flags = hkArrayBase::DONT_DEALLOCATE_FLAG;
    } else {
        newCapacity = (array->m_capacityAndFlags & hkArrayBase::CAPACITY_MASK) / 2;
        newData = hkThreadMemory::s_instance->allocateChunk(newCapacity * elemSize, 0x15);
        flags = 0;
    }
    hkString::memCpy(newData, array->m_data, array->m_size * elemSize);
    hkThreadMemory::s_instance->deallocateChunk( array->m_data, elemSize * (array->m_capacityAndFlags & hkArrayBase::CAPACITY_MASK), 0x15);
    array->m_data = newData;
    array->m_capacityAndFlags = (array->m_capacityAndFlags & hkArrayBase::FORCE_SIGN_FLAG) | (newCapacity | flags);
}

