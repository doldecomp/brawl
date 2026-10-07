#pragma force_active off
#define SO_INSTANCE_UNIT_EXTERNAL_FULL_PROPERTY_DTOR
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>
class soCollisionShieldEventObserver;

template soArrayVector<soInstanceUnitFullProperty<soCollisionShieldEventObserver*>, 4>::~soArrayVector();
