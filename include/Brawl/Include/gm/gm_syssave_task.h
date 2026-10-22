#pragma once

#include <gf/gf_system_callback.h>
#include <sr/sr_common.h>

class gmSysSave : public gfReturnStatusCallback {
public:
    static gmSysSave* create(Heaps::HeapType heap);
    virtual bool returnStatus() const;
};
