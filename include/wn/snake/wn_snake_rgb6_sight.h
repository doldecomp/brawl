#pragma once

#include <wn/weapon.h>

// Interface-only declaration for the native RGB6 sight article. Its complete
// module builder and object layout remain to be reconstructed in the natural TU.
class wnSnakeRgb6Sight : public Weapon {
public:
    void enableOperate();
    void unableOperate();
};
