//
// Created by arden on 10/18/23.
//

#include "MusicGuiOverlay.h"

MusicGuiOverlay::MusicGuiOverlay (TuxConstants::TuxInternalParameters& p, juce::Image& im) : parameters(p), image(im)
{
    parameters.wavtableX->addListener(this);
    getParamValues();
}

MusicGuiOverlay::~MusicGuiOverlay()
{
    parameters.wavtableX->removeListener(this);
}

void MusicGuiOverlay::getParamValues()
{
    paramValue = parameters.wavtableX->get();
    repaint();
}

void MusicGuiOverlay::parameterValueChanged (int parameterIndex, float newValue)
{
    getParamValues();
}

void MusicGuiOverlay::mouseUp (const juce::MouseEvent& event)
{
    *(parameters.wavtableX) = event.position.getY() / (float)getHeight();
}
void MusicGuiOverlay::mouseDrag (const juce::MouseEvent& event)
{
    *(parameters.wavtableX) = event.position.getY() / (float)getHeight();
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
