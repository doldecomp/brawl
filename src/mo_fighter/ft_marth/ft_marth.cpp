#include <ft/ft_class_info_impl.h>
#include <ft/marth/ft_marth.h>
#include <ft/marth/ft_marth_extend_param_accesser.h>
#include <if/if_marth_final.h>

#define FT_BC ftMarthBuildConfig
#include <ft/builder/ft_builder_noinline.h>

ftMarthExtendParamAccesser g_ftMarthExtendParamAccesser;

ftClassInfoImpl<Fighter_Marth, ftMarth> g_ftClassInfoMarth;

ftMarth::ftMarth(s32 entryId,
                 Heaps::HeapType instHeap,
                 Heaps::HeapType nwModelInstHeap,
                 Heaps::HeapType nwMotionInstHeap) :
    ftFighterBuilder<ftMarthBuildConfig>(entryId,
                                         Fighter_Marth,
                                         instHeap,
                                         nwModelInstHeap,
                                         nwMotionInstHeap) {
}

// FIXME: Test code present only to emit the shared builder functions; delete once ftMarth is done
void testBuilder() {
    soInsideEventManageModuleBuilder<ftMarthInsideEventManageModuleBuildConfig, ftInsideEventManageModuleTypes> insideBuilder;
    soResourceIdAccesserImpl idAccImpl(0, 1, 2);
    soPostureModuleBuilder<soPostureModuleBuildConfig<1, soPostureModuleImpl> > postureBuilder(nullptr, nullptr);
    soCollisionAttackModuleBuilder<soCollisionAttackModuleBuildConfig<soCollision::Category_Fighter, 5, 2, soCollisionAttackModuleImpl, 5, true, true> > attackBuilder(nullptr, 0, gfTask::Category(0), nullptr);
    soCollisionHitModuleBuilder<soCollisionHitModuleBuildConfig<soCollision::Category_Fighter, 20, 1, soCollisionHitModuleImpl, 0x3ff, true> > hitBuilder(nullptr, 0, gfTask::Category(0), nullptr);
}
soInsideEventManageModuleBuilder<ftMarthInsideEventManageModuleBuildConfig, ftInsideEventManageModuleTypes> g_insideBuilder;

#pragma dont_inline off

void ftMarth::photoMoved() {
    soModuleAccesser* moduleAccesser = m_moduleAccesser;
    if (moduleAccesser->getStatusModule().getStatusKind() == 0x120) {
        int count = moduleAccesser->getWorkManageModule().getInt(0x20000016);
        if (count > 0) {
            for (int i = 0; i < count; i++) {
                IfMarthFinalTask* window = dynamic_cast<IfMarthFinalTask*>(gfTask::getTask(moduleAccesser->getWorkManageModule().getInt(0x20000004 + i)));
                if (window != NULL) {
                    window->setVisibilityWhole(false);
                }
            }
        }
    }
}

void ftMarth::photoExit() {
    soModuleAccesser* moduleAccesser = m_moduleAccesser;
    if (moduleAccesser->getStatusModule().getStatusKind() == 0x120) {
        int count = moduleAccesser->getWorkManageModule().getInt(0x20000016);
        if (count > 0) {
            for (int i = 0; i < count; i++) {
                IfMarthFinalTask* window = dynamic_cast<IfMarthFinalTask*>(gfTask::getTask(moduleAccesser->getWorkManageModule().getInt(0x20000004 + i)));
                if (window != NULL) {
                    window->setVisibilityWhole(true);
                }
            }
        }
    }
}
