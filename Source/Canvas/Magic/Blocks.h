//
// Created by arden on 9/10/23.
//

#ifndef TUXPAINTVST_BLOCKS_H
#define TUXPAINTVST_BLOCKS_H

#include "MagicBase.h"

namespace Magic {
    class Blocks : public MagicBase
    {
    public:
        Blocks();
        [[nodiscard]] juce::Image getIcon() const override;
        [[nodiscard]] std::string getName() const override;
        [[nodiscard]] std::string getDescription() const override;

    private:
        void click(int x, int y) override;
        void drag(int ox, int oy, int x, int y) override;
        void drawAlongLine(int x, int y) override;

        const int EFFECT_REZ = 4;
    };
}


#endif //TUXPAINTVST_BLOCKS_H
