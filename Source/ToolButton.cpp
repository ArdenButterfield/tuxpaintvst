//
// Created by arden on 7/22/23.
//

#include "ToolButton.h"

ToolButton::ToolButton(juce::String name) : juce::Button(name) {}
ToolButton::~ToolButton() {}
void ToolButton::paintButton (juce::Graphics &g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) {
    g.setColour(juce::Colours::white);
    g.drawRect(getLocalBounds());
}
