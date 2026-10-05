#pragma once

#include <havok/hkSingleton.h>

// Error reporting singleton (vtable defined in the base system unit).
struct hkError : hkSingleton<hkError> {
    virtual void message(int level, int id, const char* description, const char* file, int line);
    virtual void setEnabled(int id, bool enabled);
    virtual bool isEnabled(int id);
    virtual void enableAll();
    virtual void sectionBegin(const char* name);
    virtual void sectionEnd();
};

void hkErrorMessage(const char* msg);
