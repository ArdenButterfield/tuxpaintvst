//
// Created by arden on 9/6/23.
//

#include "MagicGraphics.h"
MagicGraphics::MagicGraphics (juce::AudioProcessorValueTreeState& p) : parameters(p)
{
    auto magictype = (dynamic_cast<juce::AudioParameterChoice*>(parameters.getParameter("magictype")))->getIndex();
    auto effectindex = (dynamic_cast<juce::AudioParameterChoice*>(parameters.getParameter(Magic::magic_ids[magictype])))->getIndex();
    parameters.addParameterListener("magictype", this);
    for (const auto& id : Magic::magic_ids) {
        parameters.addParameterListener(id, this);
    }
    currentMagicEffect = Magic::magicEffects[magictype][effectindex];
    currentMagicEffect->setCanvasImage(canvasImage);
    mode = Magic::MODE_FULLSCREEN; // TODO: have this be changeable.
}

MagicGraphics::~MagicGraphics()
{
    parameters.addParameterListener("magictype", this);
    for (const auto& id : Magic::magic_ids) {
        parameters.addParameterListener(id, this);
    }
}
void MagicGraphics::doMouseDown (int x, int y)
{
    currentMagicEffect->prepareToDraw();
    currentMagicEffect->click(mode, x, y);
    prevX = x; prevY = y;
}
void MagicGraphics::doMouseDragged (int x, int y)
{
    currentMagicEffect->drag(prevX, prevY, x, y);
    prevX = x; prevY = y;
}
void MagicGraphics::doMouseUp (int x, int y)
{
    currentMagicEffect->release(x, y);
}
void MagicGraphics::parameterChanged (const juce::String& parameterID, float newValue)
{
    currentMagicEffect = Magic::getCurrentMagicEffect(parameters);
    currentMagicEffect->setCanvasImage(canvasImage);
}
void MagicGraphics::setImage (juce::Image* im)
{
    GraphicsBase::setImage (im);
    currentMagicEffect->setCanvasImage(im);
}
