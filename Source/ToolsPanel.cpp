//
// Created by arden on 7/22/23.
//

#include "ToolsPanel.h"

ToolsPanel::ToolsPanel(juce::AudioProcessorValueTreeState& p)
    : parameters(p)
{
    toolSlider = std::make_unique<juce::Slider>();
    toolAttachment = std::make_unique<SliderAttachment>(parameters, "tool", *toolSlider);
    gd_tools = {7,2};
    cur_tool = TOOL_BRUSH;
    old_tool = TOOL_BRUSH;
    parameters.addParameterListener("tool", this);
    for (int i = 0; i < NUM_TOOLS; ++i) {
        tool_avail[i] = 1;
        auto button = new NamedToolButton(juce::String(tool_names[i]), i, buttonIcons[i]);
        toolButtons.add(button);
        addAndMakeVisible(button);
        button->addListener(this);
    }
}
ToolsPanel::~ToolsPanel() {
    toolButtons.clear(true);
    parameters.removeParameterListener("tool", this);
}

void ToolsPanel::paint (juce::Graphics& g) {
    g.setColour(juce::Colours::white);
    g.fillAll();
}

void ToolsPanel::resized() {
    auto buttonWidth = getWidth() / numColumns;
    for (int i = 0; i < NUM_TOOLS; ++i) {
        auto col = i % numColumns;
        auto row = i / numColumns;
        toolButtons[i]->setBounds(col * buttonWidth, row * buttonWidth, buttonWidth, buttonWidth);
    }
}

void ToolsPanel::buttonClicked (juce::Button* b)
{
    ToolButton* button = dynamic_cast<ToolButton*>(b);
    if (button == nullptr || button->toolID == cur_tool || !button->isButtonOn()) {
        return;
    }
    toolButtons[cur_tool]->setDown(false);
    old_tool = cur_tool;
    cur_tool = button->toolID;
    button->setDown(true);

    auto param = dynamic_cast<juce::AudioParameterChoice*>(parameters.getParameter("tool"));
    if (param != nullptr) {
        *param = cur_tool;
    }
}

void ToolsPanel::parameterChanged (const juce::String& parameterID, float newValue)
{
    auto param = dynamic_cast<juce::AudioParameterChoice*>(parameters.getParameter(parameterID));
    if (param != nullptr) {
        toolButtons[cur_tool]->setDown(false);
        old_tool = cur_tool;
        cur_tool = param->getIndex();
        toolButtons[cur_tool]->setDown(true);
    }
}
