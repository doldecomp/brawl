#include <types.h>
#include <sr/sr_revision.h>

static const u16 RevisionNumber = 32032;

u16 srSystemGetRevisionNumber() {
    return RevisionNumber;
}
