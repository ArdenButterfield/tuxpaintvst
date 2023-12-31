//
// Created by arden on 8/29/23.
//

#ifndef TUXPAINTVST_BUTTONSELECTOR_H
#define TUXPAINTVST_BUTTONSELECTOR_H

#include "juce_audio_processors/juce_audio_processors.h"
#include "juce_graphics/juce_graphics.h"
#include "juce_gui_basics/juce_gui_basics.h"

#include "../BinaryDataHeaders/BinaryDataUI.h"
#include "../ScrollButton.h"
#include "../ToolButton.h"
#include "../TuxConstants.h"

class ButtonSelector : public juce::Component, public juce::AudioProcessorParameter::Listener
{
public:
    ButtonSelector (juce::AudioParameterChoice* param, const std::vector<juce::Image>& icons);
    ~ButtonSelector();
    void resized() override;
    void paint (juce::Graphics& g) override;

private:

    void mouseDown (const juce::MouseEvent& event) override;
    void mouseWheelMove (const juce::MouseEvent& event, const juce::MouseWheelDetails& wheel) override;

    const std::vector<juce::Image>& buttonIcons;
    int selectionIndex;
    int firstDisplayedIcon;
    int rows;
    int cols;
    const int buttonWidth = TuxConstants::buttonWidth;
    const int buttonHeight = TuxConstants::buttonHeight;

    const juce::Image buttonUpBackground = juce::ImageCache::getFromMemory (BinaryDataUI::btn_up_png, BinaryDataUI::btn_up_pngSize);
    const juce::Image buttonDownBackground = juce::ImageCache::getFromMemory (BinaryDataUI::btn_down_png, BinaryDataUI::btn_down_pngSize);
    const juce::Image buttonOffBackground = juce::ImageCache::getFromMemory (BinaryDataUI::btn_off_png, BinaryDataUI::btn_off_pngSize);

    const juce::Image scrollUpOn = juce::ImageCache::getFromMemory(BinaryDataUI::scroll_up_png, BinaryDataUI::scroll_up_pngSize);
    const juce::Image scrollUpOff = juce::ImageCache::getFromMemory(BinaryDataUI::scroll_up_off_png, BinaryDataUI::scroll_up_off_pngSize);
    const juce::Image scrollDownOn = juce::ImageCache::getFromMemory(BinaryDataUI::scroll_down_png, BinaryDataUI::scroll_down_pngSize);
    const juce::Image scrollDownOff = juce::ImageCache::getFromMemory(BinaryDataUI::scroll_down_off_png, BinaryDataUI::scroll_down_off_pngSize);

    juce::AudioParameterChoice* parameterToAttachTo;
    int numVisibleButtons;
    void parameterValueChanged (int parameterIndex, float newValue) override;
    void parameterGestureChanged (int parameterIndex, bool gestureIsStarting) override {};
};

#endif //TUXPAINTVST_BUTTONSELECTOR_H
