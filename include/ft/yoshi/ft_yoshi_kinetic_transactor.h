#pragma once

#include <mt/mt_vector.h>

class soModuleAccesser;

// Yoshi's custom kinetic modes are dispatched from the fighter kinetic mediator.
class ftYoshiKineticTransactor {
public:
    static void changeKinetic(int mode, void* pools, soModuleAccesser* acc);
    static void changeKineticSub(bool* result, void* pools, Vec2f* speed, soModuleAccesser* acc);
    static void changeKineticSub1(bool* result, void* pools, Vec2f* speed, soModuleAccesser* acc);
    static void changeKineticSub2(bool* result, void* pools, Vec2f* speed, soModuleAccesser* acc);
    static void changeKineticSub3(bool* result, void* pools, Vec2f* speed, soModuleAccesser* acc);
    static void changeKineticSub4(bool* result, void* pools, Vec2f* speed, soModuleAccesser* acc);
};
