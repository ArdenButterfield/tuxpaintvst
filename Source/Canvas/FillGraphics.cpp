//
// Created by arden on 8/30/23.
//

#include "FillGraphics.h"

FillGraphics::FillGraphics(juce::AudioProcessorValueTreeState& p)
     : parameters(p)
{
    parameters.addParameterListener("colors", this);
}

FillGraphics::~FillGraphics()
{
    parameters.removeParameterListener("colors", this);
}

void FillGraphics::parameterChanged(const juce::String &parameterID, float newValue)
{
    auto ind = dynamic_cast<juce::AudioParameterChoice*>(parameters.getParameter("colors"))->getIndex();
    color = TuxConstants::default_color_hexes[ind];
}
void FillGraphics::doMouseDown (int x, int y)
{
    doFill(x, y, juce::Colours::greenyellow);
}

void FillGraphics::doMouseDragged (int x, int y)
{
    doFill(x,y,juce::Colours::magenta);
}

void FillGraphics::doFill (int x, int y, juce::Colour fillColor)
{
    if (canvasImage == nullptr) {
        return;
    }
    juce::Graphics g(*canvasImage);
    g.setColour(color); // TEMP
    g.fillAll();
}