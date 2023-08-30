//
// Created by arden on 8/29/23.
//

#ifndef TUXPAINTVST_BUTTONSELECTOR_H
#define TUXPAINTVST_BUTTONSELECTOR_H

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_graphics/juce_graphics.h>
#include <juce_gui_basics/juce_gui_basics.h>

#include "BinaryDataHeaders/BinaryDataUI.h"
#include "ToolButton.h"
#include "ScrollButton.h"

class ButtonSelector : public juce::Component, public juce::AudioProcessorValueTreeState::Listener
{
public:
    ButtonSelector(juce::AudioProcessorValueTreeState& p, juce::String parameterID, const std::vector<juce::Image>& icons);
    ~ButtonSelector();
    void resized() override;
    void paint(juce::Graphics &g) override;
private:
    const std::vector<juce::Image>& buttonIcons;
    juce::OwnedArray<ToolButton> buttons;
    ScrollButton scrollUp;
    ScrollButton scrollDown;
    int selectionIndex;
    int firstDisplayedIcon;
    int rows;
    int cols;
    const int buttonWidth = 48;
    const int buttonHeight = 48;

    juce::AudioProcessorValueTreeState& parameters;
    juce::String parameterID;

    void parameterChanged (const juce::String &parameterID, float newValue) override;
};

#endif //TUXPAINTVST_BUTTONSELECTOR_H
