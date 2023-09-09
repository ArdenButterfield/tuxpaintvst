//
// Created by arden on 9/6/23.
//

#include "MagicOptionPanel.h"

MagicOptionPanel::MagicOptionPanel(juce::AudioProcessorValueTreeState& p)
    : OptionsPanel(p, "Magic"), parameters(p)
{

    for (int type = 0; type < Magic::NUM_MAGIC_TYPES; ++type) {
        auto& effects = Magic::magicEffects[type];
        for (auto& effect : effects) {
            icons[type].push_back(effect->getIcon());
        }
        buttonSelectors.add(new ButtonSelector(p, Magic::magic_ids[type], icons[type]));
    }
    currentButtonSelector = 0;
    addAndMakeVisible(buttonSelectors[currentButtonSelector]);
}

MagicOptionPanel::~MagicOptionPanel()
{
    buttonSelectors.clear(true);
}

void MagicOptionPanel::paint (juce::Graphics& g)
{
    g.drawImageAt (buttonNav, prevButtonBounds.getX(), prevButtonBounds.getY());
    g.drawImageAt (buttonNav, nextButtonBounds.getX(), nextButtonBounds.getY());
    auto prevInnerBounds = prevButtonBounds.withSizeKeepingCentre (prevIcon.getWidth(), prevIcon.getHeight());
    auto nextInnerBounds = nextButtonBounds.withSizeKeepingCentre (nextIcon.getWidth(), nextIcon.getHeight());
    g.drawImageAt (prevIcon, prevInnerBounds.getX(), prevInnerBounds.getY());
    g.drawImageAt (nextIcon, nextInnerBounds.getX(), nextInnerBounds.getY());
}

void MagicOptionPanel::resized()
{
    titlePanel.setBounds(getLocalBounds().withHeight(40));
    for (auto& selector : buttonSelectors) {
        selector->setBounds(getLocalBounds().withTrimmedTop(40).withTrimmedBottom(TuxConstants::buttonHeight));
    }
    auto navArea = getLocalBounds().withHeight(TuxConstants::buttonHeight).withBottomY(getBottom());
    prevButtonBounds = navArea.withTrimmedRight(TuxConstants::buttonWidth);
    nextButtonBounds = navArea.withTrimmedLeft(TuxConstants::buttonWidth);
}

void MagicOptionPanel::mouseDown (const juce::MouseEvent& event)
{
    if (prevButtonBounds.contains(event.position.roundToInt())) {
        setMagicPane(currentButtonSelector - 1);
        auto p = (dynamic_cast<juce::AudioParameterChoice*>(parameters.getParameter("magictype")));
        *p = currentButtonSelector;
    } else if (nextButtonBounds.contains(event.position.roundToInt())) {
        setMagicPane(currentButtonSelector - 1);
        auto p = (dynamic_cast<juce::AudioParameterChoice*>(parameters.getParameter("magictype")));
        *p = currentButtonSelector;
    }
}

void MagicOptionPanel::parameterChanged (const juce::String& parameterID, float newValue)
{
    setMagicPane(dynamic_cast<juce::AudioParameterChoice*>(parameters.getParameter("magictype"))->getIndex());
}
void MagicOptionPanel::setMagicPane (int index)
{
    if (index == currentButtonSelector) {
        return;
    }
    removeChildComponent(buttonSelectors[currentButtonSelector]);
    index += buttonSelectors.size();
    index %= buttonSelectors.size();
    currentButtonSelector = index;
    addAndMakeVisible(buttonSelectors[currentButtonSelector]);
    repaint();
}
