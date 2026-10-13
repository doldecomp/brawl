#pragma once

#include <wn/wn_em_simple.h>

class wnemTabooProc {
public:
    static void BodySplitBulletFly(wnemSimple* wn);
    static void BodySplitBulletExplosion(wnemSimple* wn);
    static void CometBulletFly(wnemSimple* wn);
    static void CometBulletExplosion(wnemSimple* wn);
};
