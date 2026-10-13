#pragma once

#include <StaticAssert.h>
#include <snd/snd_id.h>
#include <so/so_module_accesser.h>
#include <so/sound/so_sound_module_impl.h>

class ftSoundIdExchangerImpl : public soSoundIdExchanger {
public:
    virtual ~ftSoundIdExchangerImpl();
    virtual SndID getId(SndID sndID, soModuleAccesser* moduleAccesser);
    virtual int getStepId(int);
    virtual int getLandingId(int);
    virtual bool isVoiceId(int);
    virtual bool isVoiceMute(int);
};

class ftKirbySoundIdExchangerImpl : public ftSoundIdExchangerImpl {
public:
    virtual ~ftKirbySoundIdExchangerImpl();
    virtual bool isVoiceId(int);
};

extern ftSoundIdExchangerImpl g_ftSoundIdExchangerImpl;
extern ftKirbySoundIdExchangerImpl g_ftKirbySoundIdExchangerImpl;
