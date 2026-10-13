#pragma once

#include <gf/gf_task.h>

namespace utility {

class StandardTask : public gfTask {
public:
    virtual void processDefault();
    virtual ~StandardTask();

    virtual bool preLoad();
    virtual void loadResource() = 0;
    virtual bool checkLoadFinish() const;
    virtual void setupScene();
    virtual void createModel() = 0;
    virtual void update() = 0;
};

class StandardMenu : public StandardTask {
public:
    virtual void processDefault();
    virtual ~StandardMenu();
};

}
