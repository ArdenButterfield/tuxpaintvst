//
// Created by arden on 9/5/23.
//

#ifndef TUXPAINTVST_MAGICBASE_H
#define TUXPAINTVST_MAGICBASE_H

#include "juce_audio_processors/juce_audio_processors.h"
#include "juce_graphics/juce_graphics.h"
#include "../../BinaryDataHeaders/BinaryDataMagicIcons.h"
#include "MagicModes.h"

namespace Magic {

    class MagicBase
    {
    public:
        MagicBase() : canvasImage(nullptr) {}
        virtual ~MagicBase() = default;
        void setCanvasImage(juce::Image* im) { canvasImage = im; }
        [[nodiscard]] virtual juce::Image getIcon() const {return {};}
        [[nodiscard]] virtual std::string getName() const { return "";}
        [[nodiscard]] virtual std::string getDescription() const {return "";}
        virtual void switchIn() {}
        virtual void switchOut() {}
        virtual void click(int mode, int x, int y) {}
        virtual void drag(int ox, int oy, int x, int y) {}
        virtual void release(int x, int y) {}
        virtual bool requireColors() {return false;}
        virtual int modes() {return 0;}
    protected:
        juce::Image* canvasImage;
    };

}

#endif //TUXPAINTVST_MAGICBASE_H
