#include <ef/ef_screen_handle.h>

bool efScreenHandle::isValid() const {
    return (unk0 >= 0 && unk0 < 10);
}
