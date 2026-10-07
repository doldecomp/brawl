#pragma force_active off
#define SO_INSTANCE_UNIT_EXTERNAL_FULL_PROPERTY_DTOR
#define SO_ATTRIBUTE_FLAG_TRIVIAL_DTOR
#include <so/templates/so_instance_manager.h>

class soCollisionAttackEventObserver;

typedef soCollisionAttackEventObserver* Elm;
typedef soInstanceManagerFullPropertyNull<Elm> Mgr;

template void Mgr::set(Elm const&, s32);
template u32 Mgr::size() const;
template bool Mgr::isContain(s32) const;
template void Mgr::getPriorityArray(soArray<Elm*>&);
template void Mgr::getAttributeArray(soAttributeFlag, soArray<Elm*>&);
template soAttributeFlag Mgr::getAttribute(s32) const;
template s32 Mgr::getId(s32);
template u32 Mgr::capacity();
