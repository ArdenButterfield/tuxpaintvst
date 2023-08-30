//
// Created by arden on 7/22/23.
//

#include "ToolButton.h"

ToolButton::ToolButton (const juce::String name, const int _toolID, const juce::Image icon) : juce::Button (name),
                                                                                              toolID (_toolID),
                                                                                              on (true),
                                                                                              down (false),
                                                                                              buttonIcon (&icon)
{
    setInterceptsMouseClicks (true, false);
    setToggleable (true);
}
ToolButton::~ToolButton() {}

void ToolButton::paintButton (juce::Graphics& g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
    if (down)
    {
        g.drawImage (buttonDownBackground, juce::Rectangle<float> (0, 0, getWidth(), getHeight()));
    }
    else if (on)
    {
        g.drawImage (buttonUpBackground,
            juce::Rectangle<float> (0, 0, getWidth(), getHeight()));
    }
    else
    {
        g.drawImage (buttonOffBackground,
            juce::Rectangle<float> (0, 0, getWidth(), getHeight()));
    }
    if (buttonIcon) {
        g.drawImage (*buttonIcon, juce::Rectangle<float> ((getWidth() - 40) / 2, 3, 40, 40));
    }
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
    down = _down;
    repaint();
}
bool ToolButton::isButtonOn() const
{
    return on;
}
bool ToolButton::isButtonDown() const
{
    return down;
}
void ToolButton::setIcon (const juce::Image* icon)
{
    buttonIcon = icon;
}
