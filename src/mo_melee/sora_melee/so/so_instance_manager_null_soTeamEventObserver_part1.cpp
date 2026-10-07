#pragma force_active off
#define SO_INSTANCE_UNIT_EXTERNAL_FULL_PROPERTY_DTOR
#define SO_ATTRIBUTE_FLAG_TRIVIAL_DTOR
#include <so/templates/so_instance_manager.h>

class soTeamEventObserver;

typedef soTeamEventObserver* Elm;
typedef soInstanceManagerFullPropertyNull<Elm> Mgr;

template s32 Mgr::add(Elm&, s32, soAttributeFlag, s16);
template void Mgr::erase(s32);
template void Mgr::clear();
