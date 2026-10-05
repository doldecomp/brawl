#pragma once
// SHADOW of BrawlHeaders/so/link/so_link_event_presenter.h: addObserver is inline in the fighter RELs (FT_MODULE_BUILDER)

#include <StaticAssert.h>
#include <types.h>
#include <so/event/so_event_presenter.h>

class StageObject;
class soModuleAccesser;

struct soLinkEventArgs {
    int m_eventKind;
    bool _0x4;
protected:
    inline soLinkEventArgs(int eventKind) : m_eventKind(eventKind), _0x4(false) {}
};
static_assert(sizeof(soLinkEventArgs) == 8, "Class is wrong size!");


class soLinkEventObserver : public soEventObserver<soLinkEventObserver> {
public:
    typedef u16 AttributeMask;
    static const AttributeMask ATTRIBUTE_MASK_NONE = 0;
    struct AttributeFlag {
        union {
            struct {
                bool : 1;
                bool : 1;
                bool : 1;
                bool : 1;
                bool : 1;
                bool : 1;
                bool : 1;
                bool : 1;
                bool : 1;
                bool : 1;
                bool : 1;
                bool : 1;
                bool : 1;
                bool : 1;
                bool : 1;
                bool : 1;
            };
            AttributeMask m_mask;
        };
        inline AttributeFlag() : m_mask(ATTRIBUTE_MASK_NONE) {}
        inline AttributeFlag(AttributeMask bits) : m_mask(bits) {}
        inline ~AttributeFlag() {}

        AttributeFlag(soAttributeFlag f) : m_mask(f.m_mask) { }
        operator soAttributeFlag() { return soAttributeFlag(m_mask); }
    };

    soLinkEventObserver(short unitID) : soEventObserver<soLinkEventObserver>(unitID) {};

#ifdef FT_MODULE_BUILDER
    virtual void addObserver(short param1, s8 param2) { addObserverSub(param1, this, param2); } // MATCH-ONLY: inline in the REL
#else
    virtual void addObserver(short param1, s8 param2);
#endif
    virtual void notifyEventLink(soLinkEventArgs *eventInfo, soModuleAccesser* moduleAccesser, StageObject*, int unk4);
};
static_assert(sizeof(soLinkEventObserver) == 12, "Class is wrong size!");
