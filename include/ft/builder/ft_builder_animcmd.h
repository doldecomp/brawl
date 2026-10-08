#pragma once

// soAnimCmdModuleBuilder<soAnimCmdModuleBuildConfig<11, soAnimCmdModuleImpl>> (0xF4 bytes): ctor / dtor in the REL.
//   soAnimCmdModuleBuilder(s16 unitId); the soAnimCmdModuleImpl is at +0, its soInstanceManagerFullPropertyVector at +0x24.
// ftAnimCmdModuleSubBuilder<ftAnimCmdModuleSubBuildConfig<289, 501>> (0x15EC bytes in the module accesser builder after the
// 0x10-byte soArrayContractibleTable<const soStatusData>): eleven soAnimCmdControlUnitBuilder<...> members (one per
// anim cmd thread kind: the disguise unit, units 1-8, the uniq unit 9 and unit 10), built in the ftModuleAccesserBuilder
// constructor.

#include <ft/builder/ft_dol_types.h>
#include <ft/builder/ft_builder_status.h>
#include <ft/ft_fighter_build_data.h>
#include <ac/ac_cmd_interpreter.h>
#include <so/anim/so_anim_cmd_module_impl.h>
#include <so/so_instance_manager.h>
#include <so/so_module_accesser.h>
#include <types.h>

#include <ft/builder/ft_dol_instances.h>

FT_DOL_ARRAY_VECTOR(soInstanceUnitFullProperty<soAnimCmdControlUnit>, 11);
typedef const acAnimCmdConv* acAnimCmdConvPtr;
FT_DOL_ARRAY_VECTOR(acAnimCmdConvPtr, 289);
FT_DOL_ARRAY_VECTOR(acAnimCmdConvPtr, 288);
FT_DOL_ARRAY_VECTOR(acCmdInterpreterStackData, 8);
FT_DOL_ARRAY_VECTOR(acCmdInterpreterStackData, 10);

// MATCH-ONLY: the constructor of this instance manager (and its vtable) are in sora_melee; only the destructor is
// emitted in the REL. Explicit specialization with the members declared but not defined.
template <>
class soInstanceManagerFullPropertyVector<soAnimCmdControlUnit, 11> : public soInstanceManagerFullProperty<soAnimCmdControlUnit> {
    soArrayVector<soInstanceUnitFullProperty<soAnimCmdControlUnit>, 11> m_arrayVector; // 0x10
    bool m_unk1;
public:
    soInstanceManagerFullPropertyVector(bool p1);
    ~soInstanceManagerFullPropertyVector() { }
    virtual soAnimCmdControlUnit& at(s32 id);
    virtual soAnimCmdControlUnit& atIndex(s32 idx);
    virtual s32 getId(s32 idx);
    virtual u32 size() const;
    virtual bool isContain(s32 id) const;
    virtual void erase(s32 id);
    virtual void clear();
    virtual void set(const soAnimCmdControlUnit& elm, s32 id);
    virtual s32 add(soAnimCmdControlUnit& elm, s32 id, soAttributeFlag attr, s16 p4);
    virtual u32 capacity();
    virtual soAnimCmdControlUnit& atIndexFast(s32 idx);
    virtual soInstanceUnitFullProperty<soAnimCmdControlUnit>& atUnitIndexFast(s32 idx);
    virtual s32 getIndex(s32 id) const;
    virtual void getAttributeArray(soAttributeFlag targetAttr, soArray<soAnimCmdControlUnit*>& arr);
    virtual soAttributeFlag getAttribute(s32 id) const;
    virtual void getPriorityArray(soArray<soAnimCmdControlUnit*>& arr);
};
static_assert(sizeof(soInstanceManagerFullPropertyVector<soAnimCmdControlUnit, 11>) == 0xD0, "Class is wrong size!");

// MATCH-ONLY: soArrayContractibleTable<T> instances whose constructor and destructor are in sora_melee.
#define FT_DOL_CONTRACTIBLE_TABLE(T)                                                           \
    template <>                                                                                \
    class soArrayContractibleTable<T> : public soArrayContractible<T>,                         \
                                        public soConnectable<soArrayContractibleTable<T> > {   \
        T* m_elements;                                                                         \
        s32 m_size;                                                                            \
    public:                                                                                    \
        soArrayContractibleTable();                                                                    soArrayContractibleTable(T* elements, s32 size);                                       \
        virtual ~soArrayContractibleTable();                                                   \
        virtual T& at(s32 index);                                                              \
        virtual const T& at(s32 index) const;                                                  \
        virtual void shift();                                                                  \
        virtual void pop();                                                                    \
        virtual void clear();                                                                  \
        virtual s32 size() const;                                                              \
        virtual bool isNull() const;                                                           \
    };                                                                                         \
    static_assert(sizeof(soArrayContractibleTable<T>) == 0x10, "Class is wrong size!")

FT_DOL_CONTRACTIBLE_TABLE(acAnimCmdConvPtr);

// MATCH-ONLY: the null array (constructor, destructor in sora_melee) behind the REL-local singleton below.
template <>
class soArrayNull<const acAnimCmdConv*> : public soArray<const acAnimCmdConv*> {
public:
    soArrayNull();
    virtual ~soArrayNull();
    virtual bool isNull() const;
    virtual const acAnimCmdConv*& at(s32 index);
    virtual const acAnimCmdConv* const& at(s32 index) const;
    virtual s32 size() const;
    virtual void shift();
    virtual void pop();
    virtual void clear();
    virtual void unshift(const acAnimCmdConv* const&);
    virtual void push(const acAnimCmdConv* const&);
    virtual void insert(s32, const acAnimCmdConv* const&);
    virtual void erase(s32);
    virtual s32 capacity() const;
    virtual bool isFull() const;
    virtual void set(s32 startingIndex, const acAnimCmdConv* const& element, s32 numIndicesToSet);
};

// Null objects of sora_melee used as the unused slots of the address packs.
extern char g_soAnimCmdAddrArrayNull[];        // soArrayNull<const acAnimCmdConv*>
extern char g_soAnimCmdAddressPackArrayNull[]; // null soArrayFixed<soAnimCmdAddressPackConv>

template <typename T>
class soSingletonHolder {
public:
    static T* getInstance() {
        static T instance;
        return &instance;
    }
};

// soArrayUtility::pushRange
class soArrayUtility {
public:
    template <typename T>
    static void pushRange(soArray<T>* array, const T* src, s32 count);
};

// Header specialization must have inline linkage when shared by status units.
// MATCH-ONLY: never inlined in the original build.
#pragma dont_inline on
template <>
inline void soArrayUtility::pushRange<acAnimCmdConvPtr>(soArray<acAnimCmdConvPtr>* array, const acAnimCmdConvPtr* src, s32 count) {
    if (src == 0 || count <= 0)
        return;
    for (s32 i = 0; i < count; i++) {
        array->push(src[i]);
    }
}
#pragma dont_inline off

// soArraySelectHolder: see ft_builder_status.h

typedef soSingletonHolder<soArrayNull<const acAnimCmdConv*> > soAnimCmdNullArrayHolder;

// HYPOTHESIS: first members of the control unit builders are held by a wrapper whose inline destructor keeps the
// null check of `this` (seen in the unit destructors).
template <class T>
class soAnimCmdFirstMember {
public:
    T m_member;
    template <class P>
    soAnimCmdFirstMember(P elements, s32 size) : m_member(elements, size) { }
    soAnimCmdFirstMember(s32 size) : m_member(size) { }
    ~soAnimCmdFirstMember() { }
};

// MATCH-ONLY: address of a temporary that lives in the frame of the (inlined) caller.
inline const u8* ftAddressOf(u8 value) {
    return &value;
}

// The manage id is read through the soEventManager part of the event manage module.
inline s16 ftGetManageId(soModuleAccesser* acc) {
    soEventManager& manager = acc->getEventManageModule();
    return manager.getManageId();
}

////////////////////////////////////////
// soAnimCmdModuleBuilder
////////////////////////////////////////

template <u32 N, typename T>
class soAnimCmdModuleBuildConfig {
public:
    typedef T ModuleType;
    enum { ControlUnitNum = N };
};

template <typename BC>
class soAnimCmdModuleBuilder {
    typename BC::ModuleType m_module; // +0
    soInstanceManagerFullPropertyVector<soAnimCmdControlUnit, BC::ControlUnitNum> m_controlUnits; // +0x24
public:
    ~soAnimCmdModuleBuilder() { }
    soAnimCmdModuleBuilder(s16 unitId) : m_module(unitId, &m_controlUnits), m_controlUnits(false) { }
    typename BC::ModuleType* getModule() { return &m_module; }
};

////////////////////////////////////////
// soAnimCmdControlUnitBuilder
////////////////////////////////////////

// Id: thread kind, Attr: soAttributeFlag mask the unit is registered with, Cap: capacity of the command table.
template <int Id, int Attr, int Cap, int Unk0, int Unk1, int Mode, int Unk2, int StackCap>
class soAnimCmdControlUnitBuildConfig {
public:
    enum { UnitId = Id, AttrMask = Attr, Capacity = Cap, InterpMode = Mode, StackCapacity = StackCap };
};

template <class BC>
class soAnimCmdControlUnitBuilder {
    typedef soArrayContractibleTable<const acAnimCmdConv*> TableT;
    typedef soArrayVector<acCmdInterpreterStackData, BC::StackCapacity> StackT;
    soAnimCmdFirstMember<TableT> m_table;                                                                   // +0
    u32 unk10;                                                                                              // +0x10
    soArraySelectHolder<1, StackT, soSingletonHolder<soArrayNull<acCmdInterpreterStackData> > > m_stack;   // +0x14
    soAnimCmdAddressPackArraySeparate m_pack;                                                               // +0xC0
    soAnimCmdInterpreter m_interpreter;                                                                     // +0xDC
public:
    soAnimCmdControlUnitBuilder(soModuleAccesser* acc, void* data0, void* data1, void* data2) :
        m_table((const acAnimCmdConv**)data0, BC::Capacity),
        m_stack(),
        m_pack(&m_table.m_member, (soArrayFixed<const acAnimCmdConv*>*)g_soAnimCmdAddrArrayNull, (soArrayFixed<const acAnimCmdConv*>*)g_soAnimCmdAddrArrayNull),
        m_interpreter(ftGetManageId(acc), &m_stack.m_array, BC::UnitId, BC::InterpMode, 1.0f, ftAddressOf((u8)0)) {
        soAttributeFlag attr(BC::AttrMask);
        soAnimCmdControlUnit unit = { &m_interpreter, &m_pack };
        acc->getAnimCmdModule().registInterpreter(unit, attr);
    }
};

// Unit 9: no command table / address pack of its own (uses the null pack), a deeper interpreter stack.
template <int Id, int StackCap>
class soAnimCmdControlUnitBuildConfigUniq {
public:
    enum { UnitId = Id, StackCapacity = StackCap };
};

template <class BC>
class soAnimCmdControlUnitBuilderUniq {
    soAnimCmdInterpreter m_interpreter;                                                                     // +0
    soArraySelectHolder<1, soArrayVector<acCmdInterpreterStackData, BC::StackCapacity>, soSingletonHolder<soArrayNull<acCmdInterpreterStackData> > > m_stack; // +0x50
public:
    soAnimCmdControlUnitBuilderUniq(soModuleAccesser* acc) :
        m_interpreter(ftGetManageId(acc), (soArrayVector<acCmdInterpreterStackData, 8>*)&m_stack.m_array, BC::UnitId, 1, 1.0f, ftAddressOf((u8)1)),
        m_stack() {
        soAttributeFlag attr(4);
        soAnimCmdControlUnit unit;
        unit.m_animCmdInterpreter = &m_interpreter;
        unit.m_animCmdAddressPackArraySeparate = (soAnimCmdAddressPackArraySeparate*)g_soAnimCmdAddressPackArrayNull;
        acc->getAnimCmdModule().registInterpreter(unit, attr);
    }
};

// Unit 0: the two disguise lists (Cap entries each) instead of a command table.
template <int Id, int Attr, int Cap, int Cap2, int Unk1, int Mode, int Unk2, int StackCap>
class soAnimCmdControlUnitBuildConfigDisguise {
public:
    enum { UnitId = Id, AttrMask = Attr, Capacity = Cap, InterpMode = Mode, StackCapacity = StackCap };
};

struct soAnimCmdDisguiseListEntry {
    s32 index;
    const acAnimCmdConv* value;
};

template <class BC>
class soAnimCmdControlUnitBuilderDisguise {
    typedef soArrayVector<const acAnimCmdConv*, BC::Capacity> ListT;
    typedef soArrayVector<acCmdInterpreterStackData, BC::StackCapacity> StackT;
    soAnimCmdFirstMember<ListT> m_list0;                                                                     // +0
    soArraySelectHolder<1, ListT, soAnimCmdNullArrayHolder> m_list1;                                         // +0x490
    u32 unk920;                                                                                              // +0x920
    soArraySelectHolder<1, StackT, soSingletonHolder<soArrayNull<acCmdInterpreterStackData> > > m_stack;    // +0x924
    soAnimCmdAddressPackArraySeparate m_pack;                                                                // +0x9D0
    soAnimCmdInterpreter m_interpreter;                                                                      // +0x9EC
public:
    soArray<const acAnimCmdConv*>* getEntryList(int index) {
        switch (index) {
        case 0:
            return &m_list0.m_member;
        case 1:
            return &m_list1.m_array;
        case 2:
            return soAnimCmdNullArrayHolder::getInstance();
        default:
            return soAnimCmdNullArrayHolder::getInstance();
        }
    }

    void setupDisguiseList(int index, soAnimCmdDisguiseListEntry* list) {
        soArray<const acAnimCmdConv*>* entries = getEntryList(index);
        if (entries->isNull() != true && list != nullptr) {
            for (s32 i = 0;; i++) {
                if (i >= entries->capacity())
                    break;
                if (list[i].index < 0)
                    break;
                const acAnimCmdConv* conv = list[i].value;
                entries->at(list[i].index) = conv;
            }
        }
    }

    soAnimCmdControlUnitBuilderDisguise(soModuleAccesser* acc) :
        m_list0(0),
        m_list1(),
        m_stack(),
        m_pack(&m_list0.m_member, &m_list1.m_array, soAnimCmdNullArrayHolder::getInstance()),
        m_interpreter(ftGetManageId(acc), &m_stack.m_array, BC::UnitId, BC::InterpMode, 1.0f, ftAddressOf((u8)0)) {
        soArrayUtility::pushRange<const acAnimCmdConv*>(&m_list0.m_member, (const acAnimCmdConv* const*)0, BC::Capacity);
        soArrayUtility::pushRange<const acAnimCmdConv*>(&m_list1.m_array, (const acAnimCmdConv* const*)0, BC::Capacity);
        soArrayUtility::pushRange<const acAnimCmdConv*>(soAnimCmdNullArrayHolder::getInstance(), (const acAnimCmdConv* const*)0, 0);
        soAttributeFlag attr(BC::AttrMask);
        soAnimCmdControlUnit unit = { &m_interpreter, &m_pack };
        acc->getAnimCmdModule().registInterpreter(unit, attr);
    }
};

////////////////////////////////////////
// ftAnimCmdModuleSubBuilder
////////////////////////////////////////

template <u32 NodeNum, u32 CmdNum>
class ftAnimCmdModuleSubBuildConfig {
public:
    typedef soAnimCmdControlUnitBuildConfigDisguise<0, 1, NodeNum, NodeNum, 0, 1, 0, 8> Unit0Config;
    typedef soAnimCmdControlUnitBuildConfig<1, 2, CmdNum, 0, 0, 1, 0, 8> Unit1Config;
    typedef soAnimCmdControlUnitBuildConfig<2, 64, CmdNum, 0, 0, 1, 0, 8> Unit2Config;
    typedef soAnimCmdControlUnitBuildConfig<3, 64, CmdNum, 0, 0, 1, 0, 8> Unit3Config;
    typedef soAnimCmdControlUnitBuildConfig<4, 2, CmdNum, 0, 0, 1, 0, 8> Unit4Config;
    typedef soAnimCmdControlUnitBuildConfig<5, 32, CmdNum, 0, 0, 1, 0, 8> Unit5Config;
    typedef soAnimCmdControlUnitBuildConfig<6, 128, CmdNum, 0, 0, 1, 0, 8> Unit6Config;
    typedef soAnimCmdControlUnitBuildConfig<7, 128, CmdNum, 0, 0, 1, 0, 8> Unit7Config;
    typedef soAnimCmdControlUnitBuildConfig<8, 32, CmdNum, 0, 0, 1, 0, 8> Unit8Config;
    typedef soAnimCmdControlUnitBuildConfigUniq<9, 10> Unit9Config;
    typedef soAnimCmdControlUnitBuildConfig<10, 16, 41, 0, 0, 1, 0, 8> Unit10Config;
};

template <typename BC>
class ftAnimCmdModuleSubBuilder {
public:
    soAnimCmdControlUnitBuilderDisguise<typename BC::Unit0Config> m_unit0; // +0
private:
    soAnimCmdControlUnitBuilder<typename BC::Unit1Config> m_unit1;
    soAnimCmdControlUnitBuilder<typename BC::Unit2Config> m_unit2;
    soAnimCmdControlUnitBuilder<typename BC::Unit3Config> m_unit3;
    soAnimCmdControlUnitBuilder<typename BC::Unit4Config> m_unit4;
    soAnimCmdControlUnitBuilder<typename BC::Unit5Config> m_unit5;
    soAnimCmdControlUnitBuilder<typename BC::Unit6Config> m_unit6;
    soAnimCmdControlUnitBuilder<typename BC::Unit7Config> m_unit7;
    soAnimCmdControlUnitBuilder<typename BC::Unit8Config> m_unit8;
    soAnimCmdControlUnitBuilderUniq<typename BC::Unit9Config> m_unit9;
    soAnimCmdControlUnitBuilder<typename BC::Unit10Config> m_unit10;
public:
    ftAnimCmdModuleSubBuilder(soModuleAccesser* acc, const ftFighterBuildData& fbd) :
        m_unit0(acc), m_unit1(acc, fbd.getAnimCmdData(1, 0), fbd.getAnimCmdData(1, 1), fbd.getAnimCmdData(1, 2)), m_unit2(acc, fbd.getAnimCmdData(2, 0), fbd.getAnimCmdData(2, 1), fbd.getAnimCmdData(2, 2)), m_unit3(acc, fbd.getAnimCmdData(3, 0), fbd.getAnimCmdData(3, 1), fbd.getAnimCmdData(3, 2)), m_unit4(acc, fbd.getAnimCmdData(4, 0), fbd.getAnimCmdData(4, 1), fbd.getAnimCmdData(4, 2)),
        m_unit5(acc, fbd.getAnimCmdData(5, 0), fbd.getAnimCmdData(5, 1), fbd.getAnimCmdData(5, 2)), m_unit6(acc, fbd.getAnimCmdData(6, 0), fbd.getAnimCmdData(6, 1), fbd.getAnimCmdData(6, 2)), m_unit7(acc, fbd.getAnimCmdData(7, 0), fbd.getAnimCmdData(7, 1), fbd.getAnimCmdData(7, 2)), m_unit8(acc, fbd.getAnimCmdData(8, 0), fbd.getAnimCmdData(8, 1), fbd.getAnimCmdData(8, 2)), m_unit9(acc), m_unit10(acc, fbd.getAnimCmdData(10, 0), fbd.getAnimCmdData(10, 1), fbd.getAnimCmdData(10, 2)) { }
    ~ftAnimCmdModuleSubBuilder() { }
    soAnimCmdControlUnitBuilderDisguise<typename BC::Unit0Config>* getDisguiseUnit() { return &m_unit0; }
};
