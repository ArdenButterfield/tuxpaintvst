//
// Created by arden on 9/6/23.
//

#ifndef TUXPAINTVST_MAGICGRAPHICS_H
#define TUXPAINTVST_MAGICGRAPHICS_H

#include "GraphicsBase.h"
#include "../TuxConstants.h"
#include "Magic/MagicConstants.h"

class MagicGraphics : public GraphicsBase, public juce::AudioProcessorValueTreeState::Listener
{
public:
    explicit MagicGraphics(juce::AudioProcessorValueTreeState& p);
    ~MagicGraphics() override;
private:
    void doMouseDown(int x, int y) override;
    void doMouseDragged(int x, int y) override;
    void doMouseUp(int x, int y) override;

    void setImage(juce::Image* im) override;

    void parameterChanged(const juce::String &parameterID, float newValue) override;

    Magic::MagicBase* currentMagicEffect;
    int mode;
    int prevX, prevY;

    juce::AudioProcessorValueTreeState& parameters;
};

#endif //TUXPAINTVST_MAGICGRAPHICS_H
