//
// Created by arden on 8/29/23.
//

#include "NamedToolButton.h"

NamedToolButton::NamedToolButton(const juce::String name, const int _toolID, const juce::Image icon)
    : ToolButton(name, _toolID, icon),
      defaultTypeface(juce::Typeface::createSystemTypefaceFor(BinaryDataFonts::default_font_ttf, BinaryDataFonts::default_font_ttfSize))

{
    nameFont = juce::Font(defaultTypeface).withHeight(15);

}

void NamedToolButton::paintButton (juce::Graphics &g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) {
    juce::Image * image;
    if (down) {
        g.drawImage(buttonDownBackground, juce::Rectangle<float>(0, 0,getWidth(),getHeight()));
    } else if (on) {
        g.drawImage(buttonUpBackground,
            juce::Rectangle<float>(0, 0,getWidth(),getHeight()));

    } else {
        g.drawImage(buttonOffBackground,
            juce::Rectangle<float>(0, 0,getWidth(),getHeight()));

    }
    g.drawImage(buttonIcon, juce::Rectangle<float>((getWidth() - 40) / 2, 3,40, 30)); // tool images are 30 x 40
    g.setFont(nameFont);
    g.setColour(juce::Colours::black);
    g.drawText(getName(), getLocalBounds().withTrimmedTop(getHeight() * 3/4 - 4), juce::Justification::centred);
}