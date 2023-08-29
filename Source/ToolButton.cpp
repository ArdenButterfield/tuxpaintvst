//
// Created by arden on 7/22/23.
//

#include "ToolButton.h"

ToolButton::ToolButton(const juce::String name, const int _toolID, const juce::Image icon) : juce::Button(name), toolID(_toolID), on(true), down(false), buttonIcon(icon)
{
    setInterceptsMouseClicks(true, false);
    setToggleable(true);
}
ToolButton::~ToolButton() {}

void ToolButton::paintButton (juce::Graphics &g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) {
    juce::Image * image;
    if (!on) {
        g.drawImage(buttonOffBackground, juce::Rectangle<float>(0, 0,getWidth(),getHeight()));
    } else if (!down) {
        g.drawImage(buttonUpBackground, juce::Rectangle<float>(0, 0,getWidth(),getHeight()));
    } else {
        g.drawImage(buttonDownBackground, juce::Rectangle<float>(0, 0,getWidth(),getHeight()));
    }
    g.drawImage(buttonIcon, juce::Rectangle<float>((getWidth() - 40) / 2, 3,40, 30)); // tool images are 30 x
}

void ToolButton::resized()
{
}
void ToolButton::setOn (bool _on)
{
    on = _on;
    repaint();
}
void ToolButton::setDown (bool _down)
{
    down =  _down;
    repaint();
}
bool ToolButton::isOn() const
{
    return on;
}
bool ToolButton::isDown() const
{
    return down;
}
