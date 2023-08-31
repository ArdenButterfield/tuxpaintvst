//
// Created by arden on 8/30/23.
//

#ifndef TUXPAINTVST_FILLGRAPHICS_H
#define TUXPAINTVST_FILLGRAPHICS_H

#include "GraphicsBase.h"
#include "../TuxConstants.h"

class FillGraphics : public GraphicsBase, public juce::AudioProcessorValueTreeState::Listener
{
public:
    FillGraphics(juce::AudioProcessorValueTreeState& p);
    ~FillGraphics();
    void parameterChanged(const juce::String &parameterID, float newValue) override;

    void doMouseDown(int x, int y) override;
    void doMouseDragged(int x, int y) override;
    void doMouseUp(int x, int y) override {}

private:
    juce::Colour color;

    juce::AudioProcessorValueTreeState& parameters;
    void doFill(int x, int y, juce::Colour fillColor);
};

#endif //TUXPAINTVST_FILLGRAPHICS_H
