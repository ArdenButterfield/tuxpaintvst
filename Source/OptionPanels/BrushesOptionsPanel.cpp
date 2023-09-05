//
// Created by arden on 8/29/23.
//

#include "BrushesOptionsPanel.h"

std::vector<juce::Image> makeThumbnails(const std::vector<juce::Image>& icons) {
    auto thumbnails = std::vector<juce::Image>();
    for (const auto& icon: icons) {
        if (icon.getHeight() > 40 || icon.getWidth() > 40) {
            const auto start = icon.getHeight() > 40 ? icon.getHeight() / 3 : 0;
            const auto w = start == 0 ? icon.getHeight() : start;
            thumbnails.push_back(icon.getClippedImage({start, start, w, w}));
        } else {
            thumbnails.push_back(icon.createCopy());
        }
    }
    return thumbnails;
}

BrushesOptionsPanel::BrushesOptionsPanel(juce::AudioProcessorValueTreeState& p)
    : OptionsPanel(p, "Brushes"),
      thumbnailIcons(makeThumbnails(brush_icons)),
      brushSelector(p, "brushes",thumbnailIcons)
{
    addAndMakeVisible(brushSelector);

}

BrushesOptionsPanel::~BrushesOptionsPanel()
{

}

void BrushesOptionsPanel::paint (juce::Graphics& g)
{

}
void BrushesOptionsPanel::resized()
{
    titlePanel.setBounds(getLocalBounds().withHeight(40));
    brushSelector.setBounds(getLocalBounds().withTrimmedTop(40));
}
