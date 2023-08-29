//
// Created by arden on 8/29/23.
//

#ifndef TUXPAINTVST_COLORBUTTON_H
#define TUXPAINTVST_COLORBUTTON_H

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_graphics/juce_graphics.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include "BinaryDataHeaders/BinaryDataUI.h"

class ColorButton : public juce::Button

{
public:
    ColorButton(juce::String name, int id, juce::Colour color);
    ~ColorButton();
    void resized() override;
    const int optionID;
    void setDown(bool down);
    bool isButtonDown() const;
private:
    const juce::Colour color;
    void paintButton (juce::Graphics &g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;
    bool down;
    const juce::Image buttonUpBackground = juce::ImageCache::getFromMemory(BinaryDataUI::btn_up_png, BinaryDataUI::btn_up_pngSize);
    const juce::Image buttonDownBackground = juce::ImageCache::getFromMemory(BinaryDataUI::btn_down_png, BinaryDataUI::btn_down_pngSize);
};

#endif //TUXPAINTVST_COLORBUTTON_H
