//
// Created by arden on 7/22/23.
//

#include "ToolsPanel.h"

ToolsPanel::ToolsPanel() {
    gd_tools = {7,2};
    cur_tool = TOOL_BRUSH;
    for (int i = 0; i < NUM_TOOLS; ++i) {
        tool_avail[i] = 1;
        auto button = new ToolButton(juce::String(tool_names[i]));
        toolButtons.add(button);
    }
}
ToolsPanel::~ToolsPanel() {
    toolButtons.clear(true);
}
void ToolsPanel::paint (juce::Graphics& g) {
    g.setColour(juce::Colours::magenta);
    g.fillAll();
}
void ToolsPanel::resized() {
    gd_tools.cols = 2;

    real_tools = getLocalBounds();
}
void ToolsPanel::mouseDown (const juce::MouseEvent& event) {
    int whicht = grid_hit_gd(real_tools, (int)event.mouseDownPosition.x, (int)event.mouseDownPosition.y, gd_tools);
    std::cout << whicht << "\n";
    // TODO: block right click- not so easy in JUCE
    if (whicht < NUM_TOOLS) {
        if ((cur_tool == TOOL_TEXT && whicht != TOOL_TEXT &&
                whicht != TOOL_NEW && whicht != TOOL_OPEN &&
                whicht != TOOL_SAVE) ||
            (cur_tool == TOOL_LABEL && whicht != TOOL_LABEL &&
                whicht != TOOL_NEW && whicht != TOOL_OPEN &&
                whicht != TOOL_SAVE))
        {
        }
    }

}