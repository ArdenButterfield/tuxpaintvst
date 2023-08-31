//
// Created by arden on 8/30/23.
//

#ifndef TUXPAINTVST_ERASERGRAPHICS_H
#define TUXPAINTVST_ERASERGRAPHICS_H

#include "GraphicsBase.h"
#include "../TuxConstants.h"

class EraserGraphics : GraphicsBase, juce::AudioProcessorValueTreeState::Listener
{
public:
    EraserGraphics(juce::AudioProcessorValueTreeState& p);
    ~EraserGraphics();
    void parameterChanged(const juce::String &parameterID, float newValue) override;

    void doMouseDown(int x, int y) override;
    void doMouseDragged(int x, int y) override;
    void doMouseUp(int x, int y) override {}
private:
    juce::AudioProcessorValueTreeState& parameters;
    void doErase(int x, int y);

};

#endif //TUXPAINTVST_ERASERGRAPHICS_H
