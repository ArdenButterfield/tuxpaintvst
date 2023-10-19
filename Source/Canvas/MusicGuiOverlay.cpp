//
// Created by arden on 10/18/23.
//

#include "MusicGuiOverlay.h"

MusicGuiOverlay::MusicGuiOverlay (juce::AudioProcessorValueTreeState& p, juce::Image& im) : parameters(p), image(im)
{
    parameters.addParameterListener("wavx", this);
    getParamValues();
}

MusicGuiOverlay::~MusicGuiOverlay()
{
    parameters.removeParameterListener("wavx", this);
}

void MusicGuiOverlay::getParamValues()
{
    auto param = dynamic_cast<juce::AudioParameterFloat*>(parameters.getParameter("wavx"));
    paramValue = param->get();
    repaint();
}

void MusicGuiOverlay::parameterChanged (const juce::String& parameterID, float newValue)
{
    getParamValues();
}

void MusicGuiOverlay::mouseUp (const juce::MouseEvent& event)
{
    auto param = dynamic_cast<juce::AudioParameterFloat*>(parameters.getParameter("wavx"));
    *param = event.position.getY() / (float)getHeight();
}

void MusicGuiOverlay::mouseDrag (const juce::MouseEvent& event)
{
    auto param = dynamic_cast<juce::AudioParameterFloat*>(parameters.getParameter("wavx"));
    *param = event.position.getY() / (float)getHeight();
}

void MusicGuiOverlay::paint (juce::Graphics& g)
{
    int y = getHeight() * paramValue;
    for (int x = 0; x < getWidth(); ++x) {
        auto pix = image.getPixelAt(x, y);
        g.setColour(juce::Colour(255 - pix.getRed(), 255 - pix.getGreen(), 255 - pix.getBlue()));
        g.fillRect(x,y,1, 1);
    }
}

void MusicGuiOverlay::setImage (juce::Image& im)
{
    image = im;
}
