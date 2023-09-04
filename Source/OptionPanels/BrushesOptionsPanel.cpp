//
// Created by arden on 8/29/23.
//

#include "BrushesOptionsPanel.h"

BrushesOptionsPanel::BrushesOptionsPanel(juce::AudioProcessorValueTreeState& p) : OptionsPanel(p, "Brushes"), brushSelector(p, "brushes",icons)
{
    addAndMakeVisible(brushSelector);

}

BrushesOptionsPanel::~BrushesOptionsPanel()
{

}

void BrushesOptionsPanel::paint (juce::Graphics& g)
{

}
void BrushesOptionsPanel::resized()
{
    titlePanel.setBounds(getLocalBounds().withHeight(40));
    brushSelector.setBounds(getLocalBounds().withTrimmedTop(40));
}
