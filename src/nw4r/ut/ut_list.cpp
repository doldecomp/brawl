#include <nw4r/ut/ut_list.h>

namespace nw4r {
namespace ut {

void List_Init(List* list, u16 offset) {
    list->offset = offset;
    list->headObject = nullptr;
    list->tailObject = nullptr;
    list->numObjects = 0;
}

static inline void SetFirstObject(List* list, void* object) { // Name unknown
    Link* link = NW4R_UT_LIST_GET_LINK(*list, object);
    link->prevObject = link->nextObject = nullptr;
    list->headObject = object;
    list->tailObject = object;
    ++list->numObjects;
}

void List_Append(List* list, void* object) {
    if (list->headObject == nullptr) {
        SetFirstObject(list, object);
    } else {
        Link* link = NW4R_UT_LIST_GET_LINK(*list, object);
        link->prevObject = list->tailObject;
        link->nextObject = nullptr;
        NW4R_UT_LIST_GET_LINK(*list, list->tailObject)->nextObject = object;
        list->tailObject = object;
        ++list->numObjects;
    }
}

inline void List_Prepend(List* list, void* object) {
    if (list->headObject == nullptr) {
        SetFirstObject(list, object);
    } else {
        Link* link = NW4R_UT_LIST_GET_LINK(*list, object);
        link->prevObject = nullptr;
        link->nextObject = list->headObject;
        NW4R_UT_LIST_GET_LINK(*list, list->headObject)->prevObject = object;
        list->headObject = object;
        ++list->numObjects;
    }
}

void List_Insert(List* list, void* target, void* object) {
    if (target == nullptr) {
        List_Append(list, object);
    } else if (target == list->headObject) {
        List_Prepend(list, object);
    } else {
        void* prev = NW4R_UT_LIST_GET_LINK(*list, target)->prevObject;
        Link* link = NW4R_UT_LIST_GET_LINK(*list, object);
        Link* prevLink = NW4R_UT_LIST_GET_LINK(*list, prev);
        link->prevObject = prev;
        link->nextObject = target;
        prevLink->nextObject = object;
        NW4R_UT_LIST_GET_LINK(*list, target)->prevObject = object;
        ++list->numObjects;
    }
}

void List_Remove(List* list, void* object) {
    Link* link = NW4R_UT_LIST_GET_LINK(*list, object);
    if (link->prevObject == nullptr) {
        list->headObject = link->nextObject;
    } else {
        NW4R_UT_LIST_GET_LINK(*list, link->prevObject)->nextObject = link->nextObject;
    }
    if (link->nextObject == nullptr) {
        list->tailObject = link->prevObject;
    } else {
        NW4R_UT_LIST_GET_LINK(*list, link->nextObject)->prevObject = link->prevObject;
    }
    link->prevObject = nullptr;
    link->nextObject = nullptr;
    --list->numObjects;
}

void* List_GetNext(const List* list, const void* object) {
    if (object == nullptr) {
        return list->headObject;
    }
    return NW4R_UT_LIST_GET_LINK(*list, object)->nextObject;
}

void* List_GetPrev(const List* list, const void* object) {
    if (object == nullptr) {
        return list->tailObject;
    }
    return NW4R_UT_LIST_GET_LINK(*list, object)->prevObject;
}

void* List_GetNth(const List* list, u16 n) {
    int index = 0;
    void* object = nullptr;
    while ((object = List_GetNext(list, object)) != nullptr) {
        if (n == index) {
            return object;
        }
        ++index;
    }
    return nullptr;
}

} // namespace ut
} // namespace nw4r
