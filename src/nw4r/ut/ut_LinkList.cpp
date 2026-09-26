#include <nw4r/ut/ut_LinkList.h>

namespace nw4r {
namespace ut {
namespace detail {

inline LinkListImpl::Iterator LinkListImpl::Erase(Iterator first, Iterator last) {
    LinkListNode* node = first.mNode;
    LinkListNode* end = last.mNode;
    while (node != end) {
        node = Erase(node).mNode;
    }
    return last;
}

LinkListImpl::~LinkListImpl() {
    Clear();
}

LinkListImpl::Iterator LinkListImpl::Erase(Iterator it) {
    Iterator next = it;
    ++next;
    return Erase(it, next);
}

void LinkListImpl::Clear() {
    Erase(GetBeginIter(), GetEndIter());
}

LinkListImpl::Iterator LinkListImpl::Insert(Iterator it, LinkListNode* node) {
    LinkListNode* next = it.mNode;
    LinkListNode* prev = next->mPrev;
    node->mNext = next;
    node->mPrev = prev;
    next->mPrev = node;
    prev->mNext = node;
    ++mSize;
    return Iterator(node);
}

LinkListImpl::Iterator LinkListImpl::Erase(LinkListNode* node) {
    LinkListNode* next = node->GetNext();
    LinkListNode* prev = node->GetPrev();
    next->mPrev = prev;
    prev->mNext = next;
    --mSize;
    node->mNext = nullptr;
    node->mPrev = nullptr;
    return Iterator(next);
}

} // namespace detail
} // namespace ut
} // namespace nw4r
