//
// Created by arden on 7/22/23.
//

#include "ColorsPanel.h"

ColorsPanel::ColorsPanel(juce::AudioProcessorValueTreeState& p)
: parameters(p) {
    gd_colors.rows = colors_rows;
    gd_colors.cols = (NUM_COLORS + gd_colors.rows - 1) / gd_colors.rows;

    colorSlider = std::make_unique<juce::Slider>();
    colorAttachment = std::make_unique<SliderAttachment>(parameters, "tool", *colorSlider);
    cur_color = COLOR_BLACK;
    old_color = COLOR_BLACK;
    for (int i = 0; i < NUM_COLORS; ++i) {
        auto button = new ColorButton(juce::String(default_color_names[i]), i, default_color_hexes[i]);
        colorButtons.add(button);
        addAndMakeVisible(button);
        button->addListener(this);
    }

}

ColorsPanel::~ColorsPanel() {
    colorButtons.clear(true);

}
void ColorsPanel::paint (juce::Graphics& g) {
    g.setColour(juce::Colours::cyan);
    g.fillAll();
}

void ColorsPanel::resized() {
    auto buttonWidth = getWidth() / NUM_COLORS;
    for (int i = 0; i < NUM_COLORS; ++i) {
        colorButtons[i]->setBounds(i * buttonWidth, 0, buttonWidth, getHeight());
    }

}

void ColorsPanel::parameterChanged (const juce::String& parameterID, float newValue)
{
}

void ColorsPanel::buttonClicked (juce::Button* b)
{
    ColorButton* button = dynamic_cast<ColorButton*>(b);
    if (button == nullptr || button->optionID == cur_color) {
        return;
    }
    colorButtons[cur_color]->setDown(false);
    old_color = cur_color;
    cur_color = button->optionID;
    button->setDown(true);

}
