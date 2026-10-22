#pragma once

#include <StaticAssert.h>
#include <it/it_archive.h>
#include <it/it_customizer.h>
#include <it/it_gen_archive.h>
#include <it/item.h>
#include <so/so_dispose_instance_manager.h>
#include <types.h>
#include <bitset>

class itManager : public gfTask, public soDisposeInstanceEventObserver {
public:
    struct ItemSwitch {
        std::bitset<NUM_IT_KINDS> m_itemSwitch;

        ItemSwitch() : m_itemSwitch(0) { }
        ItemSwitch(bool val) : m_itemSwitch(val) { }
    };

    struct ItemInfo {
        u16 m_variation;
        itKind m_kind : 16;
    };

    char _76[116];
    u32 m_frameCount;
    int m_numItems;
    soArrayList<itArchive*, 128> m_itArchiveArrayList;
    bool m_drawDone;
    char _1749[3];
    soArrayList<BaseItem*, 64> m_itemArrayList;
    soArrayList<BaseItem*, 64> m_itemArrayList2;
    soArrayList<BaseItem*, 64> m_itemArrayList3;
    char _4080[25];
    u8 m_itemNums[NUM_IT_KINDS];
    char _4283[1];
    ItemInfo m_nextAssistInfo; // Note: Just uses itKind in vanilla
    int m_numAssists;
    int m_preloadAssistTimer;
    soArrayList<ItemInfo, 12> m_pokemonInfoArrayList; // Note: Just uses itKind in vanilla
    u32 m_nextPokemonIndex;
    int m_numPokemon;
    int m_numPokeballs;
    int m_preloadPokemonTimer;
    soArrayList<itGenArchive*, 3> m_genArchiveArrayList;
    ItemSwitch m_itemSwitch;
    float m_itemLotRates[NUM_IT_KINDS];
    int m_crateVariation;
    int m_smashBallDropTimer;
    char _5252[8];
    int m_smashBallDropFrame1;
    int m_smashBallDropFrame2;
    char _5268[28];
    itGenParam::Level m_genLevel;
    bool m_needsToProcess;
    char _5301[3];
    void* m_figureManager;
    char _5308[4];

    virtual void processDefault();
    virtual void processBegin();
    virtual void processUpdate();
    virtual void processFixPosition();
    virtual void processDebug();
    virtual void renderDebug();
    virtual ~itManager();

    virtual void notifyDisposeInstance(bool, int, int taskId);
    virtual void notifyDrawDone();

    bool isCompItemKindArchive(itKind kind, u32 variation, bool);
    itArchive* preloadItemKindArchive(itKind kind, u32 variation, itArchive::Type archiveType, bool);
    itGenSheetKind getRandBasicItemSheet(itGenId genKind = Item_Gen_Basic); // custom parameter
    ItemKind getLotOneItemKind(itGenSheetKind* sheetKind, itGenId genKind, ItemSwitch* itemSwitch = NULL, bool unk = false);
    BaseItem* createItem(Vec3f* safePos, Vec3f* pos, float lr, itKind kind, u32 variation = 0, int createOwnerTaskId = -1,
                         soResourceModule* resourceModule = NULL, u8 groupNo = 0, int brresId = 0xffff,
                         int texResIndex = 0, int texResId = 0xffff);
    BaseItem* createItem(Vec3f* pos, float lr, itKind kind, u32 variation = 0, int createOwnerTaskId = -1,
                         soResourceModule* resourceModule = NULL, u8 groupNo = 0, int brresId = 0xffff,
                         int texResIndex = 0, int texResId = 0xffff);
    BaseItem* createItem(itKind kind, u32 variation = 0, int createOwnerTaskId = -1, soResourceModule* resourceModule = NULL,
                         u8 groupNo = 0, int brresId = 0xffff, int texResIndex = 0, int texResId = 0xffff);
    BaseItem* createBaseItem(Vec3f* safePos, Vec3f pos, float lr, itKind kind, u32 variation, int createOwnerTaskId, int ownerTaskId, soResourceModule*, u8 groupNo, int brresId, int texResIndex, int texResId, int teamNo);
    BaseItem* createItemInstance(itCreate* create);
    int createMoney(char* unk1, Vec3f *pos, Vec2f *unk2, u32 amount, u32 unk4, u32 unk5);
    u32 getItemNum(itKind kind);
    u32 getItemNum(itKind kind, int variation, int taskId, int);
    BaseItem* getItemFromInstanceId(int instanceId);
    void removeItem(BaseItem*);
    bool preloadAssist(itKind, int variation = 0); // custom parameter


    static itManager* getInstance();
};
static_assert(sizeof(itManager) == 0x14c0, "Class is wrong size!");
