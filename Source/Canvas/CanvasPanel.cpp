//
// Created by arden on 7/22/23.
//

#include "CanvasPanel.h"

CanvasPanel::CanvasPanel(juce::AudioProcessorValueTreeState& p)
    : parameters(p),
      fillGraphics(p),
      eraserGraphics(p, backgroundColour),
      brushGraphics(p)
{
    parameters.addParameterListener("tool", this);

    for (int i = 0; i < TuxConstants::NUM_TOOLS; ++i) {
        graphicsTools[i] = nullptr;
    }
    auto toolIndex = dynamic_cast<juce::AudioParameterChoice*>(parameters.getParameter("tool"))->getIndex();
    currentGraphics = graphicsTools[toolIndex];

    graphicsTools[TuxConstants::TOOL_BRUSH] = &brushGraphics;
    graphicsTools[TuxConstants::TOOL_ERASER] = &eraserGraphics;
    graphicsTools[TuxConstants::TOOL_FILL] = &fillGraphics;
}

CanvasPanel::~CanvasPanel()
{
    parameters.removeParameterListener("tool", this);
}

void CanvasPanel::paint (juce::Graphics& g)
{
    g.drawImageAt(canvas, 0, 0);
}

void CanvasPanel::resized()
{
    canvas = juce::Image(juce::Image::RGB, getWidth(), getHeight(), false);
    for (int i = 0; i < TuxConstants::NUM_TOOLS; ++i) {
        if (graphicsTools[i] != nullptr) {
            graphicsTools[i]->setImage(&canvas);
        }
    }
    auto g = juce::Graphics(canvas);
    g.setColour(backgroundColour);
    g.fillAll();
}
void CanvasPanel::mouseDown (const juce::MouseEvent& event)
{
    if (currentGraphics != nullptr) {
        currentGraphics->doMouseDown(event.getMouseDownX(), event.getMouseDownY());
        repaint();
    }
}

void CanvasPanel::mouseDrag (const juce::MouseEvent& event)
{
    if (currentGraphics != nullptr) {
        currentGraphics->doMouseDragged((int)event.position.getX(), (int)event.position.getY());
        repaint();
    }
}

void CanvasPanel::parameterChanged (const juce::String& parameterID, float newValue)
{
    auto toolIndex = dynamic_cast<juce::AudioParameterChoice*>(parameters.getParameter("tool"))->getIndex();
    currentGraphics = graphicsTools[toolIndex];
}
void CanvasPanel::mouseUp (const juce::MouseEvent& event)
{
    if (currentGraphics != nullptr) {
        currentGraphics->doMouseUp(event.getMouseDownX(), event.getMouseDownY());
        repaint();
    }
}
