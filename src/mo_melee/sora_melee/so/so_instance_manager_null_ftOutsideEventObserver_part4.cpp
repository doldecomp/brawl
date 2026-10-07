#pragma force_active off
#define SO_INSTANCE_UNIT_EXTERNAL_FULL_PROPERTY_DTOR
#define SO_ATTRIBUTE_FLAG_TRIVIAL_DTOR
#include <so/templates/so_instance_manager.h>

class ftOutsideEventObserver;

typedef ftOutsideEventObserver* Elm;
typedef soInstanceManagerFullPropertyNull<Elm> Mgr;

template soInstanceUnitFullProperty<Elm>& Mgr::atUnitIndexFast(s32);
