//
// Created by arden on 8/30/23.
//

#include "FillOptionsPanel.h"

FillOptionsPanel::FillOptionsPanel (TuxConstants::TuxInternalParameters& p)
    : OptionsPanel(p, "Fills"), fillSelector(&(p.fillOptions), icons)
{
    addAndMakeVisible(fillSelector);
}

FillOptionsPanel::~FillOptionsPanel()
{

}

void FillOptionsPanel::paint (juce::Graphics& g)
{

}
void FillOptionsPanel::resized()
{
    titlePanel.setBounds(getLocalBounds().withHeight(40));
    fillSelector.setBounds(getLocalBounds().withTrimmedTop(40));
}
