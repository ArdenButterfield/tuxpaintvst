//
// Created by arden on 7/22/23.
//

#include "ToolButton.h"

ToolButton::ToolButton(juce::String name, int _toolID) : juce::Button(name), toolID(_toolID)
{
    setInterceptsMouseClicks(true, false);
    // setClickingTogglesState(true);
    setToggleable(true);
    setRadioGroupId(0,juce::NotificationType::dontSendNotification);
}
ToolButton::~ToolButton() {}
void ToolButton::paintButton (juce::Graphics &g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) {
    auto& image = shouldDrawButtonAsDown ? buttonDownBackground : buttonUpBackground;
    g.drawImage(image, juce::Rectangle<float>(0, 0,getWidth(),getHeight()));
}

void ToolButton::resized()
{
}