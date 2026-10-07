#pragma once

// Turn-module vtable order verified against soTurnModuleImpl and its reflector caller.
struct soTurnData {
    const float* angles;
    unsigned int endFrame;
};

class soTurnModule {
public:
    virtual ~soTurnModule();
    virtual void activate();
    virtual void set(const soTurnData* data, bool changeLr, bool isExtern, float lr);
    virtual void end();
};
