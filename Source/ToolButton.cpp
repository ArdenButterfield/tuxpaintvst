//
// Created by arden on 7/22/23.
//

#include "ToolButton.h"

ToolButton::ToolButton(const juce::String name, const int _toolID, const juce::Image icon) :
        juce::Button(name),
        toolID(_toolID),
        on(true),
        down(false),
        buttonIcon(icon),
        defaultTypeface(juce::Typeface::createSystemTypefaceFor(BinaryDataFonts::FreeSans_ttf, BinaryDataFonts::FreeSans_ttfSize))
{
    nameFont = juce::Font(defaultTypeface).withHeight(20);
    setInterceptsMouseClicks(true, false);
    setToggleable(true);
}
ToolButton::~ToolButton() {}

void ToolButton::paintButton (juce::Graphics &g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) {
    juce::Image * image;
    if (!on) {
        g.drawImage(buttonOffBackground,
            juce::Rectangle<float>(0, 0,getWidth(),getHeight()));
    } else if (!down) {
        g.drawImage(buttonUpBackground,
            juce::Rectangle<float>(0, 0,getWidth(),getHeight()));
    } else {
        g.drawImage(buttonDownBackground, juce::Rectangle<float>(0, 0,getWidth(),getHeight()));
    }
    g.drawImage(buttonIcon, juce::Rectangle<float>((getWidth() - 40) / 2, 3,40, 30)); // tool images are 30 x 40
    g.setFont(nameFont);
    g.setColour(juce::Colours::black);
    g.drawText(getName(), getLocalBounds().withTrimmedTop(getHeight() * 3/4 - 4), juce::Justification::centred);
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
bool ToolButton::isButtonOn() const
{
    return on;
}
bool ToolButton::isButtonDown() const
{
    return down;
}
