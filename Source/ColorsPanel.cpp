//
// Created by arden on 7/22/23.
//

#include "ColorsPanel.h"

ColorsPanel::ColorsPanel(TuxConstants::TuxInternalParameters& p)
: parameters(p) {
    parameters.colors.addListener(this);
    cur_color = parameters.colors.getIndex();
    old_color = cur_color;
    for (int i = 0; i < NUM_COLORS; ++i) {
        auto button = new ColorButton(juce::String(TuxConstants::default_color_names[i]), i, TuxConstants::default_color_hexes[i]);
        colorButtons.add(button);
        addAndMakeVisible(button);
        button->addListener(this);
    }

}

ColorsPanel::~ColorsPanel() {
    parameters.colors.removeListener(this);
    colorButtons.clear(true);

}
void ColorsPanel::paint (juce::Graphics& g) {
    g.setColour(juce::Colours::white);
    g.fillAll();
}

void ColorsPanel::resized() {
    auto buttonWidth = getWidth() / NUM_COLORS;
    for (int i = 0; i < NUM_COLORS; ++i) {
        colorButtons[i]->setBounds(i * buttonWidth, 0, buttonWidth, getHeight());
    }

}

void ColorsPanel::parameterValueChanged (int parameterIndex, float newValue)
{
    colorButtons[cur_color]->setDown(false);
    old_color = cur_color;
    cur_color = parameters.colors.getIndex();
    colorButtons[cur_color]->setDown(true);
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
    parameters.colors = cur_color;
    button->setDown(true);

}
