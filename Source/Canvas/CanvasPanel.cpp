//
// Created by arden on 7/22/23.
//

#include "CanvasPanel.h"

CanvasPanel::CanvasPanel(juce::AudioProcessorValueTreeState& p)
    : parameters(p), fillGraphics(p)
{
    parameters.addParameterListener("tool", this);
    currentGraphics = &fillGraphics;
}

CanvasPanel::~CanvasPanel() {
    parameters.removeParameterListener("tool", this);
}

void CanvasPanel::paint (juce::Graphics& g) {
    g.drawImageAt(canvas, 0, 0);
}

void CanvasPanel::resized() {
    canvas = juce::Image(juce::Image::RGB, getWidth(), getHeight(), true);
    fillGraphics.setImage(&canvas);
}
void CanvasPanel::mouseDown (const juce::MouseEvent& event)
{
    currentGraphics->doMouseDown(event.getMouseDownX(), event.getMouseDownY());
    repaint();
}

void CanvasPanel::mouseDrag (const juce::MouseEvent& event)
{
    currentGraphics->doMouseDragged((int)event.position.getX(), (int)event.position.getY());
    repaint();
}

void CanvasPanel::parameterChanged (const juce::String& parameterID, float newValue)
{
    auto toolIndex = dynamic_cast<juce::AudioParameterChoice*>(parameters.getParameter("tool"))->getIndex();

}
