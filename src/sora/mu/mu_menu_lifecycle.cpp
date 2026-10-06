#include <mu/mu_menu_controller.h>
#include <types.h>

// Controller entry points are named by the symbol map; their linker symbols
// remain unchanged until their own units are decompiled.
extern "C" void fn_800B96E8(muMenuController*, int);
extern "C" void fn_800B9984(muMenuController*);

class muMenu {
public:
    void init();
    void start();
    int process();
    int exit();

private:
    u8 unk0[8];
    muMenuController controllers[5];
};

void muMenu::init() {}

void muMenu::start() {
    fn_800B96E8(&controllers[0], 0);
    fn_800B96E8(&controllers[1], 1);
    fn_800B96E8(&controllers[2], 2);
    fn_800B96E8(&controllers[3], 3);
    fn_800B96E8(&controllers[4], 0xF0);
}

int muMenu::process() {
    muMenuController* controller = controllers;
    int i = 0;
    do {
        fn_800B9984(controller);
        ++i;
        ++controller;
    } while (i < 5);
    return 0;
}

int muMenu::exit() {
    return 0;
}
