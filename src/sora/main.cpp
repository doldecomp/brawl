#include <gf/gf_application.h>

void main(int argc, const char* argv[]) {
    gfApplication app;
    app.init();
    if (argc == 2) {
        app.m_bootParam.init(argc, argv);
    }
    app.mainLoop();
    app.exit();
}
