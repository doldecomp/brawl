#pragma once
class soModuleAccesser;
class ftUtil {
public:
    // Parameter order is verified from fighter callers and the shared implementation.
    static void adjustWall(soModuleAccesser*, float, float, float, int);
};
