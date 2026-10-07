#pragma force_active off
#include <so/templates/so_instance_unit.h>
class soArticleEventObserver;

template soInstanceUnitFullProperty<soArticleEventObserver*>::soInstanceUnitFullProperty(soArticleEventObserver*&, s32, soAttributeFlag, s16);
template soAttributeFlag soInstanceUnitFullProperty<soArticleEventObserver*>::getAttribute() const;
