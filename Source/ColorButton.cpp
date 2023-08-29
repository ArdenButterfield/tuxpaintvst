//
// Created by arden on 8/29/23.
//

#include "ColorButton.h"
ColorButton::ColorButton (const juce::String name, const int id, const juce::Colour c)
    : juce::Button(name),
      optionID(id),
      down(false),
      color(c)
{
    setToggleable(true);
}
ColorButton::~ColorButton()
{
}
void ColorButton::resized()
{
    Component::resized();
}

void ColorButton::setDown (bool _down)
{
    down = _down;
    repaint();
}

bool ColorButton::isButtonDown() const
{
    return down;
}
void ColorButton::paintButton (juce::Graphics& g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
    if (!down) {
        g.drawImage(buttonUpBackground,
            juce::Rectangle<float>(0, 0,getWidth(),getHeight()));
    } else {
        g.drawImage(buttonDownBackground, juce::Rectangle<float>(0, 0,getWidth(),getHeight()));
    }
    g.setColour(color);
    auto ellipse = getLocalBounds().withSizeKeepingCentre(getWidth() - 10, getHeight() - 10);
    g.fillEllipse(ellipse.getX(), ellipse.getY(), ellipse.getWidth(), ellipse.getHeight());
}
