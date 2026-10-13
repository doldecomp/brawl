#pragma once

#include <StaticAssert.h>
#include <gr/gr_yakumono.h>

class grSeqYakumono : public grYakumono {

protected:
    class SeSeqBank {
        char _0[8];
    };
    static_assert(sizeof(SeSeqBank) == 8, "Class is wrong size!");

    SeSeqBank* m_seSeqBanks;
    u32 m_numSeSeqBanks;

    char _spacer[4];

public:
    grSeqYakumono(const char* taskName);
    void createSeSeqWork(int unk1);
    void playSeSeq(float unk1, int unk2);
    void playSeSeq(float unk1, float unk2, float unk3);
    void registSeSeq(unsigned int unk1, int unk2, int unk3);

    virtual ~grSeqYakumono();
};
static_assert(sizeof(grSeqYakumono) == 348, "Class is wrong size!");