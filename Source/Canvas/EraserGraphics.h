//
// Created by arden on 8/30/23.
//

#ifndef TUXPAINTVST_ERASERGRAPHICS_H
#define TUXPAINTVST_ERASERGRAPHICS_H

#include "GraphicsBase.h"
#include "../TuxConstants.h"

class EraserGraphics : public GraphicsBase, public juce::AudioProcessorValueTreeState::Listener
{
public:
    EraserGraphics(juce::AudioProcessorValueTreeState& p, juce::Colour b);
    ~EraserGraphics();
    void parameterChanged(const juce::String &parameterID, float newValue) override;

    void doMouseDown(int x, int y) override;
    void doMouseDragged(int x, int y) override;
    void doMouseUp(int x, int y) override {}
private:
    int prevX, prevY;
    int calcEraserSize();
    juce::AudioProcessorValueTreeState& parameters;
    void doErase(int x, int y);
    void eraseLine(int x1, int y1, int x2, int y2);
    int currentEraser;
    const juce::Colour backgroundColour;
};

#endif //TUXPAINTVST_ERASERGRAPHICS_H
