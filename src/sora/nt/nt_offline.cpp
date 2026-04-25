#include <nt/nt_offline.h>
#include <types.h>

NtOffline::NtOffline() : unk4(0) { }

NtOffline::~NtOffline() { }

u32 NtOffline::getFriendIndexHaveWiiID(u64 id) {
    UnkFriendInfo* p = ntFriendInfo::getInstance()->getFriendInfo();

    for (u32 i = 0; i < UnkFriendInfo::FriendRosterLimit; i++) {
        if (p->unk350[i].unk0 && p->unk350[i].unk1) {
            u64 x = (static_cast<u64>(p->unk5B3[i].unk0) << 56) +
                    (static_cast<u64>(p->unk5B3[i].unk1) << 48) +
                    (static_cast<u64>(p->unk5B3[i].unk2) << 40) +
                    (static_cast<u64>(p->unk5B3[i].unk3) << 32) +
                    (static_cast<u64>(p->unk5B3[i].unk4) << 24) +
                    (static_cast<u64>(p->unk5B3[i].unk5) << 16) +
                    (static_cast<u64>(p->unk5B3[i].unk6) <<  8) +
                    (static_cast<u64>(p->unk5B3[i].unk7) <<  0);
            if (x == id)
                return i;
        }
    }
    return 0xFF;
}
