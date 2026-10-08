#pragma once
#include <ft/wario/ft_wario_status_uniq_process_special_s.h>
class ftWarioStatusUniqProcessSpecialSDrive : public ftWarioStatusUniqProcessSpecialSCommon {
public:
    virtual ~ftWarioStatusUniqProcessSpecialSDrive() { }
    virtual void initStatus(soModuleAccesser*);
    virtual void execStatus(soModuleAccesser*);
};
