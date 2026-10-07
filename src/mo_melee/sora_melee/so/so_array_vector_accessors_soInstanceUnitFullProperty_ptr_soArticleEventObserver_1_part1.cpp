#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>
#include <so/templates/so_array_value_soArticleEventObserver.h>

template s32 soArrayVector<soInstanceUnitFullProperty<soArticleEventObserver*>, 1>::size() const;
