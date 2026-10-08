#include <ft/wolf/ft_wolf.h>

void ftWolf::onStart(int startKind) {
    // Discard old position samples before the shared fighter startup.
    m_postureHistory->clear();
    Fighter::onStart(startKind);
}

void ftWolf::processUpdate() {
    Fighter::processUpdate();
    // Reflector collision results are consumed within one update, then reset.
    unk1cc89 = 0;
    unk1cc88 = 0;
}
