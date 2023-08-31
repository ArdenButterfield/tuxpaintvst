//
// Created by arden on 8/30/23.
//

#ifndef TUXPAINTVST_STAMPOPTIONPANEL_H
#define TUXPAINTVST_STAMPOPTIONPANEL_H

#include "juce_audio_processors/juce_audio_processors.h"
#include "juce_graphics/juce_graphics.h"
#include "juce_gui_basics/juce_gui_basics.h"

#include "ButtonSelector.h"
#include "OptionsPanel.h"


class StampOptionPanel : public OptionsPanel
{
public:
    StampOptionPanel(juce::AudioProcessorValueTreeState& p);
    ~StampOptionPanel();
    void resized() override;
    ButtonSelector stampSelector;

};

#endif //TUXPAINTVST_STAMPOPTIONPANEL_H
