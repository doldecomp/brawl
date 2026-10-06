#pragma force_active on
#include <so/so_array.h>

class ftEntry;

template void soArrayVectorAbstract<ftEntry*>::push(ftEntry* const&);
template void soArrayVectorAbstract<ftEntry*>::erase(s32);
template void soArrayVectorAbstract<ftEntry*>::clear();
