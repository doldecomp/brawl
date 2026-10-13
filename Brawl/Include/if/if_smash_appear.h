#pragma once

#include <StaticAssert.h>
#include <types.h>
#include <gf/gf_archive.h>
#include <gf/gf_task.h>

// TODO: determine class size
class IfSmashAppearTask : public gfTask {
public:
    virtual void processDefault();
    virtual ~IfSmashAppearTask();
    virtual void start(s32 p1);
    virtual void dead();
    virtual void stop(s32 p1);
    virtual void removeInfo();
    virtual bool isPlaying();
    virtual float getRate();
    virtual void onOpen();
    virtual void onClose();
    virtual void onLoop();
    virtual bool onBeginMessage();
    virtual bool onEndMessage();
    virtual void onDead();
    virtual void onChangeFace();
};

class IfFoxSmashAppearTask : public IfSmashAppearTask {
public:
    virtual void processDefault();
    virtual ~IfFoxSmashAppearTask();
    virtual void start(s32 p1);
    virtual void onClose();
    virtual void onChangeFace();
    static IfFoxSmashAppearTask* create(gfArchive *);
};
