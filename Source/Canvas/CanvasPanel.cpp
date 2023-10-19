//
// Created by arden on 7/22/23.
//

#include "CanvasPanel.h"

CanvasPanel::CanvasPanel (juce::AudioProcessorValueTreeState& p, juce::Image* c)
    : parameters(p),
      canvas(c),
      fillGraphics(p),
      eraserGraphics(p, TuxConstants::backgroundColour),
      brushGraphics(p),
      magicGraphics(p),
      musicGuiOverlay(p,*canvas)

{
    parameters.addParameterListener("tool", this);

    for (int i = 0; i < TuxConstants::NUM_TOOLS; ++i) {
        graphicsTools[i] = nullptr;
    }
    auto toolIndex = dynamic_cast<juce::AudioParameterChoice*>(parameters.getParameter("tool"))->getIndex();
    if (toolIndex == TuxConstants::TOOL_MUSIC) {
        addAndMakeVisible(musicGuiOverlay);
    }
    currentGraphics = graphicsTools[toolIndex];
    currentToolIndex = toolIndex;

    graphicsTools[TuxConstants::TOOL_BRUSH] = &brushGraphics;
    graphicsTools[TuxConstants::TOOL_ERASER] = &eraserGraphics;
    graphicsTools[TuxConstants::TOOL_FILL] = &fillGraphics;
    graphicsTools[TuxConstants::TOOL_MAGIC] = &magicGraphics;
}

CanvasPanel::~CanvasPanel()
{
    parameters.removeParameterListener("tool", this);
}

void CanvasPanel::paint (juce::Graphics& g)
{
    g.drawImageAt(*canvas, 0, 0);
}

void CanvasPanel::resized()
{
    for (int i = 0; i < TuxConstants::NUM_TOOLS; ++i) {
        if (graphicsTools[i] != nullptr) {
            graphicsTools[i]->setImage(canvas);
        }
    }

    musicGuiOverlay.setBounds(getLocalBounds());
    musicGuiOverlay.setImage(*canvas);
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
    if ((currentToolIndex == TuxConstants::TOOL_MUSIC) && (toolIndex != TuxConstants::TOOL_MUSIC)) {
        removeChildComponent(&musicGuiOverlay);
    }
    if (toolIndex == TuxConstants::TOOL_MUSIC) {
        addAndMakeVisible(musicGuiOverlay);
    }
    if (currentGraphics != graphicsTools[toolIndex]) {
        currentGraphics = graphicsTools[toolIndex];
    }
    currentToolIndex = toolIndex;
}
void CanvasPanel::mouseUp (const juce::MouseEvent& event)
{
    if (currentGraphics != nullptr) {
        currentGraphics->doMouseUp(event.position.getX(), event.position.getY());
        repaint();
    }
}
