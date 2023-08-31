//
// Created by arden on 7/22/23.
//

#ifndef TUXPAINTVST_OPTIONS_H
#define TUXPAINTVST_OPTIONS_H

#include "juce_audio_processors/juce_audio_processors.h"
#include "juce_graphics/juce_graphics.h"

#include "../ScrollButton.h"
#include "../TitlePanel.h"
#include "../TuxConstants.h"

class OptionsPanel : public juce::Component
{
public:
    OptionsPanel(juce::AudioProcessorValueTreeState& p, juce::String title);
    ~OptionsPanel();
    void paint (juce::Graphics& g) override;
    void resized() override;

protected:
    TitlePanel titlePanel;
};

#endif //TUXPAINTVST_OPTIONS_H
