#include <st_greenhill/gr_greenhill.h>

// Arms the three hit pieces once.
void grGreenhillBreak::setAttack() {
    if (unk18D != 1) {
        setAttack(0);
        setAttack(1);
        setAttack(2);
        unk18D = 1;
    }
}
