//
// Created by arden on 7/22/23.
//

#include "ColorsPanel.h"

ColorsPanel::ColorsPanel() {
    color_hexes.resize(NUM_COLORS + 3);
    color_names.resize(NUM_COLORS + 3);

    gd_colors.rows = colors_rows;
    gd_colors.cols = (NUM_COLORS + gd_colors.rows - 1) / gd_colors.rows;

    // UNIMPLEMENTED: tuxpaint.c:28902 custom colors
/*
    color_names[NUM_COLORS] = "Select a color from your drawing.";
    color_hexes[NUM_COLORS] = {0,0,0};
    NUM_COLORS++;
*/
}
ColorsPanel::~ColorsPanel() {

}
void ColorsPanel::paint (juce::Graphics& g) {
    g.setColour(juce::Colours::cyan);
    g.fillAll();
}
void ColorsPanel::resized() {
}