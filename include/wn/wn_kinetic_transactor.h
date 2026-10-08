#pragma once

class soModuleAccesser;

// HYPOTHESIS: the native policy accepts an opaque energy-pool pointer; its
// dispatch currently uses only the kinetic kind and module accesser.
class wnKineticTransactor {
public:
    static void changeKinetic(int kineticType, void* pools, soModuleAccesser* acc);
};
