//
// Created by arden on 7/22/23.
//

#include "OptionsPanel.h"

OptionsPanel::OptionsPanel(TuxConstants::TuxInternalParameters& p, juce::String title) : titlePanel(title) {
    addAndMakeVisible(titlePanel);
}
OptionsPanel::~OptionsPanel() {

}
void OptionsPanel::paint (juce::Graphics& g) {

}
void OptionsPanel::resized() {

}
