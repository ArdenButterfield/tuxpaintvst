//
// Created by arden on 8/29/23.
//

#include "ButtonSelector.h"

ButtonSelector::ButtonSelector(juce::AudioProcessorValueTreeState& p, juce::String id, const std::vector<juce::Image>& icons)
    : scrollUp("up", true),
      scrollDown("down", false),
      buttonIcons(icons),
      parameters(p),
      parameterID(id)
{
    parameters.addParameterListener(parameterID, this);
    selectionIndex = static_cast<juce::AudioParameterChoice*>(parameters.getParameter(parameterID))->getIndex();
    scrollUp.addListener(this);
    scrollDown.addListener(this);
}

ButtonSelector::~ButtonSelector()
{
    parameters.removeParameterListener(parameterID, this);
    buttons.clear(true);
}

void ButtonSelector::updateDisplayAfterScroll()
{
    if (rows * cols < buttonIcons.size()) {
        auto numVisibleButtons = (rows - 1) * cols;
        for (int i = 0; i < numVisibleButtons; ++i) {
            if (i + firstDisplayedIcon < buttonIcons.size()) {
                buttons[i]->setIcon(&(buttonIcons[i + firstDisplayedIcon]));
            } else {
                buttons[i]->setIcon(nullptr);
            }
            buttons[i]->repaint();
        }
    }
}

void ButtonSelector::resized() {
    cols = getWidth() / buttonWidth;
    rows = getHeight() / buttonHeight;
    removeAllChildren();
    buttons.clear(true);
    if (rows == 0 || cols != 2) {
        return;
    }
    if (rows * cols < buttonIcons.size()) {
        addAndMakeVisible(scrollUp);
        addAndMakeVisible(scrollDown);
        scrollUp.setBounds(getLocalBounds().withHeight(buttonHeight / 2));
        scrollDown.setBounds(getLocalBounds().withHeight(buttonHeight / 2).withBottomY(getBottom()));
        auto numVisibleButtons = (rows - 1) * cols;
        if (selectionIndex < numVisibleButtons) {
            firstDisplayedIcon = 0;
        } else {
            firstDisplayedIcon = selectionIndex - numVisibleButtons;
            if (firstDisplayedIcon % cols) {
                firstDisplayedIcon += 1;
            }
        }
        for (int i = 0; i < numVisibleButtons; ++i) {
            auto toolButton = new ToolButton("", i + firstDisplayedIcon, buttonIcons[i + firstDisplayedIcon]);
            auto x = (i % cols) * buttonWidth;
            auto y = (buttonHeight / 2) + (i / cols) * buttonHeight;
            toolButton->setBounds(x, y, buttonWidth, buttonHeight);
            addAndMakeVisible(toolButton);
            buttons.add(toolButton);
        }
    }
}
void ButtonSelector::paint (juce::Graphics& g)
{

}
void ButtonSelector::parameterChanged (const juce::String& parameterID, float newValue)
{
}
void ButtonSelector::buttonClicked (juce::Button* b)
{
    if (b == &scrollUp && scrollUp.getIsOn()) {
        firstDisplayedIcon -= 2;
    } else if (b == &scrollDown && scrollDown.getIsOn()) {
       firstDisplayedIcon += 2;
    }
}
