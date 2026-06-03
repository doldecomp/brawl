#pragma once

#include <gr/gr_yakumono.h>
#include <st_tengan/gr_tengan.h>

class grTenganBg : public grTengan {
protected:
    Vec3f *posDialgaWork;
    Vec3f *posAshibaWork;

public:
    grTenganBg(const char* taskName);
    virtual ~grTenganBg();
    virtual void update(float deltaFrame);

    //virtual void setTgtNode(char *tgtNode);
    //virtual char* getTgtNode();
    virtual void setPosDialgaWork(Vec3f* pos);
    virtual void setPosAshibaWork(Vec3f* pos);

    static grTenganBg* create(int mdlIndex, const char* tgtNodeName, const char* taskName);

};
