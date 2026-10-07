#pragma force_active off
#include <so/so_array.h>
#include <new>
class soArticle;

typedef soArticle* Elm;
typedef soArrayNull<Elm> Obj;

// MATCH-ONLY: constructing the object forces its vtable and special members into this unit.
#pragma dont_inline on
void vela_use(void* p) { new (p) Obj(); }
#pragma dont_inline reset
