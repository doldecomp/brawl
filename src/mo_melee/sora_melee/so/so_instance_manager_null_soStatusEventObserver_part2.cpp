#pragma force_active off
#define SO_INSTANCE_UNIT_EXTERNAL_FULL_PROPERTY_DTOR
#define SO_ATTRIBUTE_FLAG_TRIVIAL_DTOR
#include <so/templates/so_instance_manager.h>

class soStatusEventObserver;

typedef soStatusEventObserver* Elm;
typedef soInstanceManagerFullPropertyNull<Elm> Mgr;

template Elm& Mgr::at(s32);
template Elm& Mgr::atIndex(s32);
