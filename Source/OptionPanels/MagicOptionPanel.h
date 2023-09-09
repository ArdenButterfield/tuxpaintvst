//
// Created by arden on 9/6/23.
//

#ifndef TUXPAINTVST_MAGICOPTIONPANEL_H
#define TUXPAINTVST_MAGICOPTIONPANEL_H

#include "juce_audio_processors/juce_audio_processors.h"
#include "juce_graphics/juce_graphics.h"
#include "juce_gui_basics/juce_gui_basics.h"

#include "ButtonSelector.h"
#include "OptionsPanel.h"
#include "../TuxConstants.h"
#include "../Canvas/Magic/MagicConstants.h"

class MagicOptionPanel : public OptionsPanel
{
public:
    MagicOptionPanel(juce::AudioProcessorValueTreeState& p);
    ~MagicOptionPanel();
    void paint (juce::Graphics& g) override;
    void resized() override;
private:
    std::array<std::vector<juce::Image>, Magic::NUM_MAGIC_TYPES> icons;
    juce::OwnedArray<ButtonSelector> buttonSelectors;
    int currentButtonSelector;
};

#endif //TUXPAINTVST_MAGICOPTIONPANEL_H
