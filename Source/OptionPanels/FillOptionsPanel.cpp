//
// Created by arden on 8/30/23.
//

#include "FillOptionsPanel.h"

FillOptionsPanel::FillOptionsPanel (juce::AudioProcessorValueTreeState& p)
    : OptionsPanel(p, "Fills"), fillSelector(p, juce::String(TuxConstants::tool_names[TuxConstants::TOOL_FILL]), icons)
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
