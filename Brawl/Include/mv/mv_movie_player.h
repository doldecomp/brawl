#pragma once

#include <StaticAssert.h>
#include <types.h>

class mvMoviePlayer {
public:
    static mvMoviePlayer* getInstance();
    bool isPause() const;
    void setPause();
    void resetPause();
};
// TODO size assertion
