//
// Created by arden on 9/6/23.
//

#ifndef TUXPAINTVST_MAGICGRAPHICS_H
#define TUXPAINTVST_MAGICGRAPHICS_H

#include "GraphicsBase.h"
#include "../TuxConstants.h"
#include "Magic/MagicConstants.h"

class MagicGraphics : public GraphicsBase, public juce::AudioProcessorParameter::Listener
{
public:
    explicit MagicGraphics(TuxConstants::TuxInternalParameters& p);
    ~MagicGraphics() override;
private:
    void doMouseDown(int x, int y) override;
    void doMouseDragged(int x, int y) override;
    void doMouseUp(int x, int y) override;

    void setImage(juce::Image* im) override;

    void parameterValueChanged (int parameterIndex, float newValue) override;
    void parameterGestureChanged (int parameterIndex, bool gestureIsStarting) override {}

    Magic::MagicBase* currentMagicEffect;
    int mode;
    int prevX, prevY;

    TuxConstants::TuxInternalParameters& parameters;
};

#endif //TUXPAINTVST_MAGICGRAPHICS_H
