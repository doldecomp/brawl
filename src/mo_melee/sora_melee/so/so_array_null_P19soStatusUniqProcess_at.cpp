#pragma force_active off
#include <so/so_array.h>
class soStatusUniqProcess;

typedef soStatusUniqProcess* Elm;
typedef soArrayNull<Elm> Arr;

template Elm& Arr::at(s32);
template const Elm& Arr::at(s32) const;
