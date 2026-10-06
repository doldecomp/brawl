// Explicit instantiation of the capacity-61 interpolation vector.
// The accessor split is verified; construction and vtable ownership remain unresolved.
#include <so/posture/so_posture_module_impl.h>

template class soArrayVector<soInterpolation<Vec3f>, 61>;
