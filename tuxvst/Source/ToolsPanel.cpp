//
// Created by arden on 7/22/23.
//

#include "ToolsPanel.h"

ToolsPanel::ToolsPanel() {
    gd_tools = {2,7};
}
ToolsPanel::~ToolsPanel() {

}
void ToolsPanel::paint (juce::Graphics& g) {
    g.setColour(juce::Colours::magenta);
    g.fillAll();
}
void ToolsPanel::resized() {
    gd_tools.cols = 2;
}