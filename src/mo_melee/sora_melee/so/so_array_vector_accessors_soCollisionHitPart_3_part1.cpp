#pragma force_active on
#include <so/so_array.h>
#include <revolution/gx.h>
#include <so/collision/templates/so_collision_hit_part.h>

template s32 soArrayVector<soCollisionHitPart, 3>::getTopIndex() const;
template s32 soArrayVector<soCollisionHitPart, 3>::getLastIndex() const;
template bool soArrayVector<soCollisionHitPart, 3>::isFull() const;
template s32 soArrayVector<soCollisionHitPart, 3>::capacity() const;
template s32 soArrayVector<soCollisionHitPart, 3>::size() const;
