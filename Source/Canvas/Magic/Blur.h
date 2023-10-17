//
// Created by arden on 9/11/23.
//

#ifndef TUXPAINTVST_BLUR_H
#define TUXPAINTVST_BLUR_H

#include "MagicBase.h"

namespace Magic {
    class Blur : public MagicBase
    {
    public:
        Blur();
        [[nodiscard]] juce::Image getIcon() const override;
        [[nodiscard]] std::string getName() const override;
        [[nodiscard]] std::string getDescription() const override;

    private:
        void click(int x, int y) override;
        void drag(int ox, int oy, int x, int y) override;
        void drawAlongLine(int x, int y) override;

        void doBlurPixel(int x, int y);

        const int EFFECT_REZ = 4;
    };
}

#endif //TUXPAINTVST_BLUR_H
