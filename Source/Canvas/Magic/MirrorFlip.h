//
// Created by arden on 9/6/23.
//

#ifndef TUXPAINTVST_MIRRORFLIP_H
#define TUXPAINTVST_MIRRORFLIP_H

#include "MagicBase.h"


namespace Magic {
    class MirrorFlip : public MagicBase {
    public:
        MirrorFlip() {
            currentMode = MODE_FULLSCREEN;
            availableModes = MODE_FULLSCREEN;
        }
    protected:
        enum {
            HORIZONTAL,
            VERTICAL
        };
        void doOperation(int direction);
    };
}

#endif //TUXPAINTVST_MIRRORFLIP_H
