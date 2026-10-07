#pragma force_active off
#define SO_INSTANCE_UNIT_EXTERNAL_FULL_PROPERTY_DTOR
#define SO_ATTRIBUTE_FLAG_TRIVIAL_DTOR
#include <so/templates/so_instance_manager.h>

class soLogEventObserver;

typedef soLogEventObserver* Elm;
typedef soInstanceManagerFullPropertyNull<Elm> Mgr;

template s32 Mgr::getIndex(s32) const;
