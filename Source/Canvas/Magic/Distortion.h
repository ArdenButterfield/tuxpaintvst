//
// Created by arden on 9/9/23.
//

#ifndef TUXPAINTVST_DISTORTION_H
#define TUXPAINTVST_DISTORTION_H

#include "MagicBase.h"

namespace Magic {
    class Distortion : public MagicBase
    {
    public:
        Distortion();
        [[nodiscard]] juce::Image getIcon() const override;
        [[nodiscard]] std::string getName() const override;
        [[nodiscard]] std::string getDescription() const override;

    private:
        void click(int mode, int x, int y) override;
        void drag(int ox, int oy, int x, int y) override;
        void drawAlongLine(int x, int y) override;
        const int distortionRadius = 8;
    };
}

#endif //TUXPAINTVST_DISTORTION_H
