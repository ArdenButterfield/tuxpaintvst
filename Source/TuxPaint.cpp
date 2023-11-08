//
// Created by arden on 7/22/23.
//

#include "TuxPaint.h"



TuxPaint::TuxPaint(TuxConstants::TuxInternalParameters& p, juce::Image* canvas,  OscilloscopeData& oscData)
    : parameters(p),
      toolsPanel(p),
      colorsPanel(p),
      colorsTitlePanel("Colors"),
      toolsTitlePanel("Tools"),
      shapesOptionsPanel(p),
      fillOptionsPanel(p),
      eraserOptionPanel(p),
      canvasPanel(p, canvas),
      brushesOptionsPanel(p),
      magicOptionPanel(p),
      oscilloscopePanel(oscData)
{
    currentOptionsPanel = nullptr;
    parameters.tool.addListener(this);

    addAndMakeVisible(toolsPanel);
    addAndMakeVisible(canvasPanel);
    addAndMakeVisible(colorsPanel);
    addAndMakeVisible(infoPanel);
    addAndMakeVisible(colorsTitlePanel);
    addAndMakeVisible(toolsTitlePanel);

    addAndMakeVisible(oscilloscopePanel);

    updateRightPanel(parameters.tool.getIndex());
}
TuxPaint::~TuxPaint() {
    parameters.tool.removeListener( this);
}

void TuxPaint::paint (juce::Graphics& g) {

}

void TuxPaint::resized() {
    toolsPanel.setBounds(0, 40, 96, 336);
    canvasPanel.setBounds(96,0,TuxConstants::canvasWidth,TuxConstants::canvasHeight);

    fillOptionsPanel.setBounds(544,0,96,376);
    shapesOptionsPanel.setBounds(544,0,96,376);
    eraserOptionPanel.setBounds(544,0,96,376);
    brushesOptionsPanel.setBounds(544,0,96,376);
    magicOptionPanel.setBounds(544, 0, 96, 376);

    colorsPanel.setBounds(96,376,544,48);
    toolsTitlePanel.setBounds(0,0,96,40);
    colorsTitlePanel.setBounds(0,376,96,48);

    oscilloscopePanel.setBounds(getLocalBounds().withTrimmedTop(colorsPanel.getBottom()));
}

void TuxPaint::updateRightPanel(int toolIndex)
{
    OptionsPanel* newPanel;
    switch (toolIndex)
    {
        case TuxConstants::TOOL_FILL:
            newPanel = &fillOptionsPanel;
            break;
        case TuxConstants::TOOL_SHAPES:
            newPanel = &shapesOptionsPanel;
            break;
        case TuxConstants::TOOL_ERASER:
            newPanel = &eraserOptionPanel;
            break;
        case TuxConstants::TOOL_BRUSH:
            newPanel = &brushesOptionsPanel;
            break;
        case TuxConstants::TOOL_LINES:
            newPanel = &brushesOptionsPanel;
            break;
        case TuxConstants::TOOL_MAGIC:
            newPanel = &magicOptionPanel;
            break;
        default:
            return;
    }
    if (currentOptionsPanel) {
        removeChildComponent(currentOptionsPanel);
    }
    currentOptionsPanel = newPanel;
    addAndMakeVisible(newPanel);
}

void TuxPaint::parameterValueChanged (int parameterIndex, float newValue)
{
    updateRightPanel(parameters.tool.getIndex());
}
