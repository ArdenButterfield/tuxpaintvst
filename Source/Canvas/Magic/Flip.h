//
// Created by arden on 9/6/23.
//

#ifndef TUXPAINTVST_FLIP_H
#define TUXPAINTVST_FLIP_H

#include "MirrorFlip.h"

namespace Magic {
    class Flip : public MirrorFlip
    {
        [[nodiscard]] juce::Image getIcon() const override {
           return juce::ImageCache::getFromMemory(BinaryDataMagicIcons::flip_png, BinaryDataMagicIcons::flip_pngSize);
        }

        [[nodiscard]] std::string getName() const override {
           return "Flip";
        }

        [[nodiscard]] std::string getDescription() const override {
           return "Click to flip the picture upside-down.";
        }

        void click(int mode, int x, int y) override {
           doOperation(VERTICAL);
        }

    };
}

#endif //TUXPAINTVST_FLIP_H
