//
// Created by arden on 7/22/23.
//

#ifndef TUXPAINTVST_TOOLBUTTON_H
#define TUXPAINTVST_TOOLBUTTON_H

#include <juce_audio_processors/juce_audio_processors.h>
// #include <juce_graphics/juce_graphics.h>
#include <juce_gui_basics/juce_gui_basics.h>

class ToolButton : public juce::Button
{
public:
    ToolButton(juce::String name);
    ~ToolButton();
private:
    void paintButton (juce::Graphics &g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;
};

#endif //TUXPAINTVST_TOOLBUTTON_H
