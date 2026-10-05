#include <havok/hkStackTracer.h>

hkStackTracer::hkStackTracer() {}

hkStackTracer::~hkStackTracer() {}

void hkStackTracer::dumpStackTrace(const unsigned long* trace, int numTrace, OutputFunc output,
                                   void* context) {
    output("No stack trace available", context);
}

int hkStackTracer::getStackTrace(unsigned long* trace, int maxTrace) {
    return 0;
}
