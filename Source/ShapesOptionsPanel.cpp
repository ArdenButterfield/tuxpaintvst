//
// Created by arden on 8/29/23.
//

#include "ShapesOptionsPanel.h"

ShapesOptionsPanel::ShapesOptionsPanel(juce::AudioProcessorValueTreeState& p) : OptionsPanel(p), shapeSelector(p, juce::String("shapes"), icons)
{
    addAndMakeVisible(shapeSelector);
}

ShapesOptionsPanel::~ShapesOptionsPanel()
{

}
void ShapesOptionsPanel::paint (juce::Graphics& g)
{

}
void ShapesOptionsPanel::resized()
{
    shapeSelector.setBounds(getLocalBounds());
}
