#pragma once

#include <havok/hkSingleton.h>

// Error reporting singleton (concrete implementation: hkDefaultError in the base system unit).
struct hkError : hkSingleton<hkError> {
    virtual int message(int level, int id, const char* description, const char* file, int line) = 0;
    virtual void setEnabled(int id, hkBool enabled) = 0;
    virtual hkBool isEnabled(int id) = 0;
    virtual void enableAll() = 0;
    virtual void sectionBegin(const char* name) {}
    virtual void sectionEnd() {}
};

void hkErrorMessage(const char* msg);
