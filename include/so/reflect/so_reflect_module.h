#pragma once

#include <StaticAssert.h>
#include <so/so_null.h>

class soModuleAccesser;

// Native construction gives this interface separate soNull and soNullable
// vptrs, like soGroundModule. The complete concrete table fixes method order.
class soReflectModule : public soNull, public soNullable {
public:
    virtual ~soReflectModule();
    virtual void activate() = 0;
    virtual void deactivate() = 0;
    virtual void initInfo() = 0;
    virtual void resetInfo() = 0;
    virtual int getTaskId() = 0;
    virtual int getTeam() = 0;
    virtual float getAttackMul() = 0;
    virtual void setAttackMul(float) = 0;
    virtual float getLifeMul() = 0;
    virtual bool isReflect() = 0;
    virtual float getSpeedMul() = 0;
    // HYPOTHESIS: original source bool types; native return/store widths agree.
    virtual bool isCountMax(soModuleAccesser*) = 0;
    virtual void setNoSpeedMul(bool) = 0;
};
static_assert(sizeof(soReflectModule) == 0xC, "Reflect interface layout");
