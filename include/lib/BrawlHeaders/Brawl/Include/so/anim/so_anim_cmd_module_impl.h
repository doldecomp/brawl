#pragma once

#include <StaticAssert.h>
#include <so/anim/so_anim_cmd.h>
#include <so/so_array.h>
#include <so/event/so_event_presenter.h>
#include <so/anim/so_anim_cmd_event_presenter.h>
#include <so/status/so_status_event_presenter.h>
#include <so/so_instance_manager.h>

class soModuleAccesser;

/*
 * This class is weird, it has a bunch of data before the event presenter vtable and info,
 * but the inheritance info doesn't show any other info. I can't get the layout right while
 * inheriting the presenter, so I commented it and added a spacer.
 * 
 * There is an "acCmdInterpreter" class in the code that seems to do a lot
 * of the same things as this class, but it doesn't seem to be the missing
 * inherited object, as it is about 0x10 bigger than this class. It is perhaps
 * the case that the acCmdInterpreter inherits this, but that class doesn't
 * seem to have provided inheritance info.
 *
 * I'm leaving it like this for now, since it is still somewhat useful/usable.
 */
class soAnimCmdInterpreter /*: soEventPresenter<soAnimCmdEventObserver> */ {
public:
    char _inheritance_data[8]; // 0x0; not sure what this is.
    float m_frameSpeed; // 0x8
    soAnimCmd* m_currentCmd; // 0xC
    soAnimCmd* m_startCmd; // 0x10
    char _unk0x14[8]; // 0x14
    soAnimCmd* m_lastWaitCmd; // 0x18
    char _unk0x1C[4]; // 0x1C, event presenter vtable and fields are in here.
    float m_logicalFrame; // 0x20
};
static_assert(sizeof(soAnimCmdInterpreter) == 0x28, "Class is the wrong size!");

// The unit of soAnimCmdAddressPackArraySeparate: a triple of acAnimCmdConv*s
struct soAnimCmdAddressPackConv {
    const acAnimCmdConv* addr1;
    const acAnimCmdConv* addr2;
    const acAnimCmdConv* addr3;
};

// This class zips together three fixed-size arrays of acAnimCmdConv pointers,
// presenting the resulting aggregate as a fixed-size array of
// soAnimCmdAddressPackConv.
// The constituent arrays do not need to be identical in size; nullptrs are
// filled in to pad out any shorter arrays.
class soAnimCmdAddressPackArraySeparate : public soArrayFixed<soAnimCmdAddressPackConv>  {
    soAnimCmdAddressPackConv m_pack;
    soArrayFixed<const acAnimCmdConv*>* m_addrArr1;
    soArrayFixed<const acAnimCmdConv*>* m_addrArr2;
    soArrayFixed<const acAnimCmdConv*>* m_addrArr3;
public:
    soAnimCmdAddressPackConv atSub(s32 index) const {
        if (index < 0) {
            soAnimCmdAddressPackConv pack = { nullptr, nullptr, nullptr };
            return pack;
        }

        const acAnimCmdConv* addr1 = nullptr;
        if (index < m_addrArr3->size())
            addr1 = m_addrArr3->at(index);

        const acAnimCmdConv* addr2 = nullptr;
        if (index < m_addrArr1->size())
            addr2 = m_addrArr1->at(index);

        const acAnimCmdConv* addr3 = nullptr;
        if (index < m_addrArr2->size())
            addr3 = m_addrArr2->at(index);

        soAnimCmdAddressPackConv pack = { addr1, addr2, addr3 };
        return pack;
    }

    virtual soAnimCmdAddressPackConv& at(s32 index) {
        m_pack = atSub(index);
        return m_pack;
    }

    // UBFIX this function has a bug; don't use the reference it
    // returns! TODO flag callers of this function, if any
    virtual const soAnimCmdAddressPackConv& at(s32 index) const {
        return atSub(index);
    }

    virtual s32 size() const {
        s32 max = m_addrArr3->size();
        if (max < m_addrArr1->size())
            max = m_addrArr1->size();
        if (max < m_addrArr2->size())
            max = m_addrArr2->size();
        return max;
    }

    virtual bool isNull() const { return false; }

    soAnimCmdAddressPackArraySeparate(soArrayFixed<const acAnimCmdConv*>* addrs1,
                                      soArrayFixed<const acAnimCmdConv*>* addrs2,
                                      soArrayFixed<const acAnimCmdConv*>* addrs3) :
        m_addrArr1(addrs1), m_addrArr2(addrs2), m_addrArr3(addrs3) { }

    virtual ~soAnimCmdAddressPackArraySeparate() { }
};
static_assert(sizeof(soAnimCmdAddressPackArraySeparate) == 0x1C, "Class is the wrong size!");

class soAnimCmdControlUnit {
public:
    soAnimCmdInterpreter* m_animCmdInterpreter; // 0x0
    soAnimCmdAddressPackArraySeparate* m_animCmdAddressPackArraySeparate; // 0x4
    int m_id; // 0x8
    short m_type; // 0xC
    short m_unk;  // 0xE
};
static_assert(sizeof(soAnimCmdControlUnit) == 0x10, "Class is the wrong size!");

class soAnimCmdModule: public soNullable {
public:
    virtual void registInterpreter();
    virtual void interpretCmd();
    virtual void interpretCmdAdjust();
    virtual void interpretCmd1();
    virtual void resetInterpreter1();
    virtual void resetInterpreter2();
    virtual void resetInterpreter3();
    virtual void resetInterpreter4();
    virtual void isInterpreterAnimCmd();
    virtual void skipNextMotionGroup();
    virtual bool isAnimCmdEnd();
    virtual int getAnimCmdFrame();
    virtual void getCmdAddressPack();
    virtual void setAddressPackList();
    virtual void getInterpreterNum();
    virtual ~soAnimCmdModule();
    virtual void activate(soModuleAccesser*);
    virtual void deactivate(soModuleAccesser*);
};

namespace soAnimCmdControlUnitKind {
    enum Kind {
        ActionMain,
        SubactionMain,
        SubactionGfx,
        SubactionSfx,
        SubactionOther,
        AltSubactionMain,
        AltSubactionGfx,
        AltSubactionSfx,
        AltSubactionOther,
        InfiniteLoop,
        ActionHidden,
        Count,
    };
}

class soAnimCmdModuleImpl:
    public soAnimCmdModule,
    public soStatusEventObserver,
    public soAnimCmdEventObserver
{
public:
    soInstanceManagerFullPropertyVector<soAnimCmdControlUnit, soAnimCmdControlUnitKind::Count>* m_animCmdThreads; // 0x20
};
static_assert(sizeof(soAnimCmdModuleImpl) == 0x24, "Class is the wrong size!");

/* TODO: soAnimCmdModuleNull */
