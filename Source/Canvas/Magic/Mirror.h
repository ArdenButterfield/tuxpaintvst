//
// Created by arden on 9/6/23.
//

#ifndef TUXPAINTVST_MIRROR_H
#define TUXPAINTVST_MIRROR_H

#include "MirrorFlip.h"

namespace Magic {
    class Mirror : public MirrorFlip
    {
        juce::Image getIcon() const override {
            return juce::ImageCache::getFromMemory(BinaryDataMagicIcons::mirror_png, BinaryDataMagicIcons::mirror_pngSize);
        }

        std::string getName() const override {
            return "Mirror";
        }

        std::string getDescription() const override {
            return "Click to make a mirror image.";
        }

        void click(int mode, int x, int y) {
            doOperation(VERTICAL);
        }

    };
}

#endif //TUXPAINTVST_MIRROR_H
