#include <gf/gf_application.h>

#ifdef MATCHING
#define RTYPE void
#else
#define RTYPE int
#endif

RTYPE main(int argc, const char* argv[]) {
    gfApplication app;
    app.init();
    if (argc == 2) {
        app.m_bootParam.init(argc, argv);
    }
    app.mainLoop();
    app.exit();
}
