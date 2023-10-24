//
// Created by arden on 10/23/23.
//

#ifndef TUXPAINTVST_OSCILLOSCOPEPANEL_H
#define TUXPAINTVST_OSCILLOSCOPEPANEL_H

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_graphics/juce_graphics.h>

#include "OscilloscopeData.h"

class OscilloscopePanel : public juce::Component, public juce::Timer
{
public:
    OscilloscopePanel(OscilloscopeData& oscilloscopeData);
    ~OscilloscopePanel();
private:
    void timerCallback() override;
    void paint(juce::Graphics &g) override;
    const OscilloscopeData& data;
};

#endif //TUXPAINTVST_OSCILLOSCOPEPANEL_H
