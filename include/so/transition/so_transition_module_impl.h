#pragma once

#include <StaticAssert.h>
#include <ac/ac_anim_cmd_impl.h>
#include <so/so_enable.h>
#include <so/so_instance_manager.h>
#include <types.h>

class soModuleAccesser;

class soGeneralTerm {
public:
    soArrayContractibleTable<acCmdArgConv> m_animCmdTable;

    // MATCH-ONLY: out-of-line copy constructor (so_general_term.cpp); defined elsewhere in the REL.
    soGeneralTerm(const soGeneralTerm& other);
};
static_assert(sizeof(soGeneralTerm) == 0x10, "Class is wrong size!");

class soGeneralTermManager
{
public:
    soGeneralTerm* m_generalTerms;
    s16* m_indices;
    u16 _unk08;
    u16 m_numGeneralTerms;
    // Same as m_generalTerms?
    soGeneralTerm* m_generalTerms2;
    // Same as m_indices?
    s16* m_indices2;
};
static_assert(sizeof(soGeneralTermManager) == 0x14, "Class is wrong size!");
extern soGeneralTermManager g_soGeneralTermManager;

class soGeneralTermCache
{
public:
    soGeneralTermCache();
    ~soGeneralTermCache();
    u32 m_flags;
    u32 m_flags2;
    u32 m_buttonOnMask;
    u32 m_buttonOnMask2;
    u32 m_buttonTriggerMask;
    u32 m_buttonTriggerMask2;

    void clearAll();
    void clearController();
    bool isFlag(u32 flagID, u8* resultOut);
    bool isButtonOn(u32 buttonID, u8* resultOut);
    bool isButtonTrigger(u32 buttonID, u8* resultOut);
    void setFlag(u32 flagID, bool saveToMask2);
    void setButtonOn(u32 buttonID, bool saveToMask2);
    void setButtonTrigger(u32 buttonID, bool saveToMask2);
};
static_assert(sizeof(soGeneralTermCache) == 0x18, "Class is wrong size!");
extern soGeneralTermCache g_soGeneralTermCache;

class soTransitionInfo {
public:
    int m_groupId;
    int m_unitId;
    u32 _unk08;
#ifdef FT_MODULE_BUILDER
    soTransitionInfo() : m_groupId(-1), m_unitId(-1), _unk08(0) { }
    ~soTransitionInfo(); // MATCH-ONLY: out of line in the fighter RELs (ft_builder_noinline.h)
#endif
};
static_assert(sizeof(soTransitionInfo) == 0xC, "Class is wrong size!");

class soTransitionTerm {
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

    u8 m_flags;
    u8 _pad01;
    u16 m_targetKind;
    s16 m_generalTermIndex;
    u8 _pad06[2];

    // Checks if term currently has all of its soGeneralTerms satisfied.
    int checkEstablish(soModuleAccesser* accesserIn, u32* returnWord, soGeneralTermCache* generalTermCache);
    void addGeneralTerm(soGeneralTerm* termIn);
    void clearGeneralTerm();
};
static_assert(sizeof(soTransitionTerm) == 0x8, "Class is wrong size!");

class soTransitionTermGroup {
public:
    soEnable m_enable;
    u8 _pad01[3];
    soInstanceManagerFullPropertyEccentric<soTransitionTerm> m_transitionTermInstanceManager;
    int m_unitID;

#ifdef FT_MODULE_BUILDER
    // constructor / destructor live in sora_melee
    soTransitionTermGroup(soArray<soInstanceUnitFullProperty<soTransitionTerm> >* terms);
    ~soTransitionTermGroup();
#endif

    // Checks if any of the terms within this group currently have all of their soGeneralTerms satisfied.
    u32 checkEstablish(soModuleAccesser* moduleAccesser, u32* targetKindOut, int* termIDOut, u32* returnWord, u16* attrMask, soGeneralTermCache* generalTermCache);
    // Creates a new empty term with the specified Unit ID, resetting any existing term if necessary.
    int addTerm(int unitId, u32, soTransitionTerm* termIn, u16*);
    // Calls addGeneralTerm on registered transitionTerm whose UnitID matches the supplied value (or the last registered, if -1 is supplied).
    void addGeneralTerm(int unitID, soGeneralTerm termIn);
    // Calls addGeneralTerm on registered transitionTerm whoes ID matches m_unitID (or the last, if that value is -1);
    void addGeneralTermLastTerm(soGeneralTerm termIn);
    void enableTerm(int unitId);
    void unableTerm(int unitId);
    void clearTransitionTermAll();
    void enableTermAll();
    void unableTermAll();
    bool isFull();
};
static_assert(sizeof(soTransitionTermGroup) == 0x14, "Class is wrong size!");


class soTransitionModule {
public:
    virtual int checkEstablish(soModuleAccesser* accesser, u32* targetKindOut, int groupID, u16* attrMask, soGeneralTermCache* generalTermCache);
    virtual void enableTerm(int unitID, int groupID);
    virtual void unableTerm(int unitID, int groupID);
    virtual void enableTermAll(int groupID);
    virtual void unableTermAll(int groupID);
    virtual void enableTermGroup(int groupID);
    virtual void unableTermGroup(int groupID);
    virtual bool isEnableTermGroup(int groupID);
    virtual int addTerm(int groupID, soTransitionTerm* term, int unitID, u32 targetKind, u16* option);
    virtual void addGeneralTerm(int groupID, int unitID, soGeneralTerm* term);
    virtual void addGeneralTermLastTerm(int groupID, soGeneralTerm* term);
    virtual void clearTransitionTermAll(int groupID);
    virtual int notifyEventAnimCmd(int commandType, soArrayContractibleTable<acCmdArgConv> commandArgList, u8* option, soModuleAccesser* accesser);
    virtual soTransitionInfo* getLastTransitionInfo();
    virtual ~soTransitionModule() { }
};

class soTransitionModuleImpl : public soTransitionModule {
public:
    soArray<soTransitionTermGroup>* m_transitionTermGroupArray;
    int m_groupID;
    soTransitionInfo m_transitionInfo;
#ifdef FT_MODULE_BUILDER
    // inlined into the builders
    soTransitionModuleImpl(soArray<soTransitionTermGroup>* groups); // out of line (ft_builder_noinline.h)
    soArray<soTransitionTermGroup>* getGroups() { return m_transitionTermGroupArray; }
#endif
    virtual int checkEstablish(soModuleAccesser* accesser, u32* targetKindOut, int groupID, u16* attrMask, soGeneralTermCache* generalTermCache);
    virtual void enableTerm(int unitID, int groupID);
    virtual void unableTerm(int unitID, int groupID);
    virtual void enableTermAll(int groupID);
    virtual void unableTermAll(int groupID);
    virtual void enableTermGroup(int groupID);
    virtual void unableTermGroup(int groupID);
    virtual bool isEnableTermGroup(int groupID);
    virtual int addTerm(int groupID, soTransitionTerm* term, int unitID, u32 targetKind, u16* option);
    virtual void addGeneralTerm(int groupID, int unitID, soGeneralTerm* term);
    virtual void addGeneralTermLastTerm(int groupID, soGeneralTerm* term);
    virtual void clearTransitionTermAll(int groupID);
    virtual int notifyEventAnimCmd(int commandType, soArrayContractibleTable<acCmdArgConv> commandArgList, u8* option, soModuleAccesser* accesser);
    virtual soTransitionInfo* getLastTransitionInfo();
#ifdef FT_MODULE_BUILDER
    virtual ~soTransitionModuleImpl() { }
#else
    virtual ~soTransitionModuleImpl();
#endif
};
static_assert(sizeof(soTransitionModuleImpl) == 0x18, "Class is wrong size!");
