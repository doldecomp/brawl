#include <st/st_data_container.h>
#include <types.h>

stDataContainer::stDataContainer(stDataContainerData* data)
    : m_headerSize(HeaderSize), m_filedata(data) { }

stDataContainer::~stDataContainer() { }

// TODO: suspect that this returns a void* or u8*
stDataContainerData* stDataContainer::getData(u32 index) {
    if (m_filedata->m_numFiles <= index) {
        return nullptr;
    }
    u32* startOffsets = static_cast<u32*>(getDataAddressHead());
    return reinterpret_cast<stDataContainerData*>(
        reinterpret_cast<u8*>(m_filedata) + startOffsets[index]);
}

void* stDataContainer::getDataAddressHead() {
    return reinterpret_cast<u8*>(m_filedata) + m_headerSize;
}

stDataSimpleContainer::stDataSimpleContainer(stDataContainerData* data)
    : stDataContainer(data) {
    this->m_headerSize = SimpleHeaderSize;
}

stDataSimpleContainer::~stDataSimpleContainer() { }

