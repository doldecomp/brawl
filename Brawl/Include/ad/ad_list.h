#pragma once

#include <StaticAssert.h>
#include <sr/sr_common.h>
#include <types.h>

template<typename T>
struct adListNode {
    adListNode* m_prev;
    adListNode* m_next;
    T m_val;
};

template<typename T>
class adListInterface {
public:
    virtual u32 count() const = 0;
    virtual void reset() = 0;
    virtual T* current() = 0;
    virtual T* end() = 0;
    virtual T get() const = 0;
    virtual void set(T val) = 0;
    virtual void next() = 0;
    virtual void prev() = 0;
    virtual void pushBack(T val) = 0;
    virtual void remove() = 0;
    virtual void eraseCurrentNode() = 0;
};

template<typename T, Heaps::HeapType H>
class adList : public adListInterface<T> {
    adListNode<T>* m_start;
    adListNode<T>* m_end;
    adListNode<T>* m_current;
    u32 m_count;
public:
    virtual u32 count() const;
    virtual void reset();
    virtual T* current();
    virtual T* end();
    virtual T get() const;
    virtual void set(T val);
    virtual void next();
    virtual void prev();
    virtual void pushBack(T val);
    virtual void remove();
    virtual void eraseCurrentNode();

    adList() : m_start(nullptr), m_end(nullptr), m_current(nullptr),
            m_count(0) { }
};
