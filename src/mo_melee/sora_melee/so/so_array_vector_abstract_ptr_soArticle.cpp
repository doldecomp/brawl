#pragma force_active on
#include <so/so_array.h>

class soArticle;

template soArticle*& soArrayVectorAbstract<soArticle*>::at(s32);
template soArticle* const& soArrayVectorAbstract<soArticle*>::at(s32) const;
template void soArrayVectorAbstract<soArticle*>::unshift(soArticle* const&);
template void soArrayVectorAbstract<soArticle*>::shift();
template void soArrayVectorAbstract<soArticle*>::push(soArticle* const&);
template void soArrayVectorAbstract<soArticle*>::pop();
template void soArrayVectorAbstract<soArticle*>::insert(s32, soArticle* const&);
template void soArrayVectorAbstract<soArticle*>::erase(s32);
template void soArrayVectorAbstract<soArticle*>::set(s32, soArticle* const&, s32);
template void soArrayVectorAbstract<soArticle*>::clear();
template bool soArrayVectorAbstract<soArticle*>::isNull() const;
template void soArrayVectorAbstract<soArticle*>::substitution(s32, s32);
