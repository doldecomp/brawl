#include <gf/gf_thread.h>

// Note: This class is unused; all of its associated data and code is dead-stripped.
// Its existence is inferred from the name of the source file and from the locations
// of the vtables for gfThread and gfRunnable in the final executable.

class gfArchiveLoadThread : public gfThread {
public:
    virtual void run();
};

void gfArchiveLoadThread::run() {
    static gfArchiveLoadThread thread;
    thread.run();
}
