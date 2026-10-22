#pragma once

#include <types.h>

template<typename T>
class soConnectable {
protected:
    T* m_link;

public:
    soConnectable() : m_link(nullptr) { }
    soConnectable& operator=(const soConnectable& other) {
        if (this != &other)
            m_link = other.m_link;
        return *this;
    }

    void connect(T* node) {
        if (m_link)
            m_link->connect(node);
        else
            m_link = node;
    }
};
