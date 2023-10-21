//
// Created by arden on 7/22/23.
//

#include "ToolsPanel.h"

ToolsPanel::ToolsPanel(TuxConstants::TuxInternalParameters& p)
    : parameters(p)
{
    cur_tool = parameters.tool.getIndex();
    parameters.tool.addListener(this);
    for (int i = 0; i < TuxConstants::NUM_TOOLS; ++i) {
        tool_avail[i] = 1;
        auto button = new NamedToolButton(juce::String(TuxConstants::tool_names[i]), i, buttonIcons[i]);
        toolButtons.add(button);
        addAndMakeVisible(button);
        button->addListener(this);
    }
}
ToolsPanel::~ToolsPanel() {
    toolButtons.clear(true);
    parameters.tool.removeListener(this);
}

void ToolsPanel::paint (juce::Graphics& g) {
    g.setColour(juce::Colours::white);
    g.fillAll();
}

void ToolsPanel::resized() {
    auto buttonWidth = getWidth() / numColumns;
    for (int i = 0; i < TuxConstants::NUM_TOOLS; ++i) {
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

    parameters.tool = cur_tool;
}

void ToolsPanel::parameterValueChanged (int parameterIndex, float newValue)
{
    toolButtons[cur_tool]->setDown(false);
    old_tool = cur_tool;
    cur_tool = parameters.tool.getIndex();
    toolButtons[cur_tool]->setDown(true);
}
