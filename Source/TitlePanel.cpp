//
// Created by arden on 7/22/23.
//

#include "TitlePanel.h"

TitlePanel::TitlePanel(const juce::String _name)
    : name(_name),
      defaultTypeface(juce::Typeface::createSystemTypefaceFor(BinaryDataFonts::FreeSans_ttf, BinaryDataFonts::FreeSans_ttfSize))
{
    titleFont = juce::Font(defaultTypeface).withHeight(50);
    titleLabel.setFont(titleFont);
    titleLabel.setText(name, juce::NotificationType::dontSendNotification);
    titleLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    titleLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(background);
    addAndMakeVisible(titleLabel);
}

TitlePanel::~TitlePanel() {

}
void TitlePanel::paint (juce::Graphics& g) {
}

void TitlePanel::resized() {
    if (getHeight() > 41) {
        background.setImage(titleBackgroundBig);
    } else {
        background.setImage(titleBackground);
    }
    background.setBounds(getLocalBounds());
    titleLabel.setBounds(getLocalBounds());
}
