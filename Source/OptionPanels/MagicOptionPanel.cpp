//
// Created by arden on 9/6/23.
//

#include "MagicOptionPanel.h"

MagicOptionPanel::MagicOptionPanel(juce::AudioProcessorValueTreeState& p)
    : OptionsPanel(p, "Magic")
{
    std::cout << "magic options constructor\n";
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

}

void MagicOptionPanel::resized()
{
    buttonSelectors[currentButtonSelector]->setBounds(getLocalBounds());
}

