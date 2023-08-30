//
// Created by arden on 7/22/23.
//

#ifndef TUXPAINTVST_TOOLBUTTON_H
#define TUXPAINTVST_TOOLBUTTON_H

#include <juce_audio_processors/juce_audio_processors.h>
// #include <juce_graphics/juce_graphics.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include "BinaryDataHeaders/BinaryDataUI.h"
#include "BinaryDataHeaders/BinaryDataFonts.h"

class ToolButton : public juce::Button
{
public:
    ToolButton(juce::String name, int _toolID, juce::Image icon);
    ~ToolButton();
    void resized() override;
    const int toolID;
    void setOn(bool on);
    void setDown(bool down);
    bool isButtonOn() const;
    bool isButtonDown() const;

    void setIcon(juce::Image icon);

protected:
    void paintButton (juce::Graphics &g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;
    bool on;
    bool down;
    const juce::Image buttonUpBackground = juce::ImageCache::getFromMemory(BinaryDataUI::btn_up_png, BinaryDataUI::btn_up_pngSize);
    const juce::Image buttonDownBackground = juce::ImageCache::getFromMemory(BinaryDataUI::btn_down_png, BinaryDataUI::btn_down_pngSize);
    const juce::Image buttonOffBackground = juce::ImageCache::getFromMemory(BinaryDataUI::btn_off_png, BinaryDataUI::btn_off_pngSize);
    juce::Image buttonIcon;
    juce::ImageComponent background;
};

#endif //TUXPAINTVST_TOOLBUTTON_H
