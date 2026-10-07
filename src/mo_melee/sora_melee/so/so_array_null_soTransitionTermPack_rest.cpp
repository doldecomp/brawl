#pragma force_active off
#include <so/so_array.h>
class soTransitionTermPack;

typedef soTransitionTermPack Elm;
typedef soArrayNull<Elm> Arr;

template s32 Arr::size() const;
template void Arr::shift();
template void Arr::pop();
template void Arr::clear();
template void Arr::unshift(const Elm&);
template void Arr::push(const Elm&);
template void Arr::insert(s32, const Elm&);
template void Arr::erase(s32);
template s32 Arr::capacity() const;
template bool Arr::isFull() const;
template void Arr::set(s32, const Elm&, s32);
template bool Arr::isNull() const;
