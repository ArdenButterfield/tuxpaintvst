//
// Created by arden on 8/29/23.
//

#ifndef TUXPAINTVST_SCROLLBUTTON_H
#define TUXPAINTVST_SCROLLBUTTON_H

#include <juce_audio_processors/juce_audio_processors.h>
// #include <juce_graphics/juce_graphics.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include "BinaryDataHeaders/BinaryDataUI.h"

class ScrollButton : public juce::Button
{
public:
    ScrollButton(juce::String name, int isUp);

    bool getIsUp() {return isUp;}
    bool getIsOn() {return isOn;}
    void setIsUp(bool up) {isUp = up; repaint();}
    void setIsOn(bool on) {isOn = on; repaint();}

private:
    void paintButton (juce::Graphics &g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;
    bool isUp;
    bool isOn;

    const juce::Image buttonUpOn = juce::ImageCache::getFromMemory(BinaryDataUI::scroll_up_png, BinaryDataUI::scroll_up_pngSize);
    const juce::Image buttonUpOff = juce::ImageCache::getFromMemory(BinaryDataUI::scroll_up_off_png, BinaryDataUI::scroll_up_off_pngSize);
    const juce::Image buttonDownOn = juce::ImageCache::getFromMemory(BinaryDataUI::scroll_down_png, BinaryDataUI::scroll_down_pngSize);
    const juce::Image buttonDownOff = juce::ImageCache::getFromMemory(BinaryDataUI::scroll_down_off_png, BinaryDataUI::scroll_down_off_pngSize);

};

#endif //TUXPAINTVST_SCROLLBUTTON_H
