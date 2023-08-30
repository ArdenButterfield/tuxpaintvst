//
// Created by arden on 7/22/23.
//

#include "TuxPaint.h"



TuxPaint::TuxPaint(juce::AudioProcessorValueTreeState& p)
    : parameters(p),
      toolsPanel(p),
      colorsPanel(p),
      colorsTitlePanel("Colors"),
      toolsTitlePanel("Tools"),
      shapesOptionsPanel(p),
      fillOptionsPanel(p)
{
    currentOptionsPanel = &shapesOptionsPanel;

    parameters.addParameterListener("tool", this);
    auto param = dynamic_cast<juce::AudioParameterChoice*>(parameters.getParameter("tool"));
    if (param != nullptr) {
        updateRightPanel(param->getIndex());
    }
    addAndMakeVisible(toolsPanel);
    addAndMakeVisible(canvasPanel);
    addAndMakeVisible(fillOptionsPanel);
    addAndMakeVisible(colorsPanel);
    addAndMakeVisible(infoPanel);
    addAndMakeVisible(colorsTitlePanel);
    addAndMakeVisible(toolsTitlePanel);

}
TuxPaint::~TuxPaint() {
    parameters.removeParameterListener("tool", this);
}
void TuxPaint::paint (juce::Graphics& g) {

}
void TuxPaint::resized() {
    toolsPanel.setBounds(0, 40, 96, 336);
    canvasPanel.setBounds(96,0,448,376);
    fillOptionsPanel.setBounds(544,0,96,376);
    shapesOptionsPanel.setBounds(544,0,96,376);
    colorsPanel.setBounds(96,376,544,48);
    toolsTitlePanel.setBounds(0,0,96,40);
    colorsTitlePanel.setBounds(0,376,96,48);
}

void TuxPaint::updateRightPanel(int toolIndex)
{
    OptionsPanel* newPanel;
    switch (toolIndex)
    {
        case ToolsPanel::TOOL_FILL:
            newPanel = &fillOptionsPanel;
            break;
        case ToolsPanel::TOOL_SHAPES:
            newPanel = &shapesOptionsPanel;
            break;
        default:
            return;
    }
    removeChildComponent(currentOptionsPanel);
    currentOptionsPanel = newPanel;
    addAndMakeVisible(newPanel);
}

void TuxPaint::parameterChanged (const juce::String& parameterID, float newValue)
{
    if (parameterID == "tool") {
        auto param = dynamic_cast<juce::AudioParameterChoice*>(parameters.getParameter(parameterID));
        if (param != nullptr) {
            updateRightPanel(param->getIndex());
        }
    }
}
