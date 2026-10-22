#pragma once

#include <StaticAssert.h>
#include <types.h>

namespace nw4r {
    namespace g3d {
        struct ResBlockHeaderData {
            char kind[4];
            u32 size;
        };

        template <typename T>
        class ResCommon {
            T* m_dataPtr;

        public:
            inline ResCommon() { m_dataPtr = NULL; }
            inline ResCommon(void* data) : m_dataPtr(static_cast<T*>(data)) {}
            inline ResCommon(const void* data) : m_dataPtr(static_cast<T*>(data)) {}

            inline T& ref() const { return *m_dataPtr; }
            inline T* ptr() const { return m_dataPtr; }
            T& operator*() const { return *m_dataPtr; }
            T* operator->() const { return m_dataPtr; }
            inline bool IsValid() const { return m_dataPtr != NULL; }
        };

    } // namespace g3d
} // namespace nw4r
