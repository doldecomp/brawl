#pragma once

#include <StaticAssert.h>
#include <em/enemy.h>
#include <em/em_create.h>
#include <so/resource/so_resource_id_accesser.h>
#include <so/resource/so_resource_module_impl.h>
#include <types.h>

// TODO: Determine size
class emResourceModuleImpl : public soResourceModuleImpl {
public:
    void* unk18;
    void* unk1C;
    void* unk20;
    void* unk24;
    void* unk28;
    UnkParamAccesser* unk2C;
    void* unk30;
    UnkParamAccesser* unk34;
    EnemyKind m_kind;

    emResourceModuleImpl(
        u32 paramArchiveId,
        soResourceIdAccesserImpl* resourceIdAccessor,
        u32 emCommonArchiveId,
        emCreate* create);
    virtual ~emResourceModuleImpl();
    void ModifyParam(emCreate* create);
    nw4r::g3d::ResFileData* getInfoTexFile(u32 p1, u32 p2);

    template<typename T>
    static void ModifyExParam(emResourceModuleImpl* p1, emCreate const* create) {
        p1->unk2C = create->m_epsp ? create->m_epsp : p1->unk34;
    }

    template<typename T>
    static void DeleteExParam(emResourceModuleImpl* p1) { }
};
