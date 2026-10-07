#pragma force_active on
#define SO_INSTANCE_MANAGER_EXTERNAL_SIZE
#define SO_INSTANCE_MANAGER_EXTERNAL_AT
#include <so/templates/so_instance_manager.h>
class soCaptureEventObserver;

template void soInstanceManagerFullPropertyVector<soCaptureEventObserver*, 4>::set(soCaptureEventObserver* const&, s32);
