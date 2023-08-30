//
// Created by arden on 8/29/23.
//

#ifndef TUXPAINTVST_NAMEDTOOLBUTTON_H
#define TUXPAINTVST_NAMEDTOOLBUTTON_H

#include "ToolButton.h"

class NamedToolButton : public ToolButton
{
public:
    NamedToolButton(const juce::String name, const int _toolID, const juce::Image icon);
private:
    juce::Typeface::Ptr defaultTypeface;
    juce::Font nameFont;
    void paintButton (juce::Graphics &g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;
};

#endif //TUXPAINTVST_NAMEDTOOLBUTTON_H
