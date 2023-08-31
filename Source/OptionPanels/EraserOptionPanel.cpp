//
// Created by arden on 8/30/23.
//

#include "EraserOptionPanel.h"

std::vector<juce::Image> makeIcons(const int numErasers)
{
    std::vector<juce::Image> images;
    // Make square erasers
    const int numSquareErasers = numErasers / 2;
    for (int i = 0; i < numSquareErasers; ++i) {
        auto im = juce::Image(juce::Image::ARGB, 48, 48, true);
        juce::Graphics g(im);
        g.setColour(juce::Colour(0,0,0));
        auto sz = (2 + ((numSquareErasers - 1 - i) * (38 / (numSquareErasers - 1))));

        g.drawRect(juce::Rectangle<int>(24 - sz / 2, 24 - sz / 2, sz, sz), 2);
        images.push_back(im);
    }
    const int numCircleErasers = numErasers - numSquareErasers;
    for (int i = 0; i < numCircleErasers; ++i) {
        auto im = juce::Image(juce::Image::ARGB, 48, 48, true);
        juce::Graphics g(im);
        const auto cx = 24;
        const auto cy = 24;
        g.setColour(juce::Colour(0,0,0));
        auto sz = (2 + ((numSquareErasers - 1 - i) * (38 / (numSquareErasers - 1))));
//        g.drawEllipse(juce::Rectangle<float>(cx - sz / 2, cy - sz / 2, sz, sz), 2.0);
        for (int yy = -sz; yy <= sz; yy++)
        {
            for (int xx = -sz; xx <= sz; xx++)
            {
                int n = (xx * xx) + (yy * yy) - ((sz / 2) * (sz / 2));

                if (n >= -sz && n <= sz)
                {
                    im.setPixelAt (cx + xx, cy + yy, juce::Colour (0, 0, 0));
                }
            }
        }


        images.push_back(im);
    }
    return images;
}

EraserOptionPanel::EraserOptionPanel (juce::AudioProcessorValueTreeState& p)
    : OptionsPanel(p, "Erasers"),
      icons(makeIcons(TuxConstants::NUM_ERASERS)),
      eraserSelector(p, "erasers", icons)
{
    addAndMakeVisible(eraserSelector);
}

EraserOptionPanel::~EraserOptionPanel()
{

}

void EraserOptionPanel::paint (juce::Graphics& g)
{

}

void EraserOptionPanel::resized()
{
    titlePanel.setBounds(getLocalBounds().withHeight(40));
    eraserSelector.setBounds(getLocalBounds().withTrimmedTop(40));
}