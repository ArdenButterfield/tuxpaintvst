//
// Created by arden on 7/22/23.
//

#ifndef TUXPAINTVST_OPTIONS_H
#define TUXPAINTVST_OPTIONS_H

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_graphics/juce_graphics.h>

#include "TuxConstants.h"
#include "ScrollButton.h"

class OptionsPanel : public juce::Component
{
public:
    OptionsPanel(juce::AudioProcessorValueTreeState& p);
    ~OptionsPanel();
    void paint (juce::Graphics& g) override;
    void resized() override;
private:
    ScrollButton scrollUp;
    ScrollButton scrollDown;
};

#endif //TUXPAINTVST_OPTIONS_H
