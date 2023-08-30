//
// Created by arden on 8/29/23.
//

#include "ScrollButton.h"
ScrollButton::ScrollButton(juce::String name, int up) : juce::Button(name) {
    isUp = up;
    isOn = false;
}

void ScrollButton::paintButton (juce::Graphics &g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
    if (isOn && isUp) {
        g.drawImage(buttonUpOn, juce::Rectangle<float>(0, 0,getWidth(),getHeight()));
    } else if (isUp) {
        g.drawImage(buttonUpOff, juce::Rectangle<float>(0, 0,getWidth(),getHeight()));
    } else if (isOn) {
        g.drawImage(buttonDownOn, juce::Rectangle<float>(0, 0,getWidth(),getHeight()));
    } else {
        g.drawImage(buttonDownOff, juce::Rectangle<float>(0, 0,getWidth(),getHeight()));
    }
}