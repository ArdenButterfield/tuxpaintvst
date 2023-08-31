//
// Created by arden on 8/30/23.
//

#ifndef TUXPAINTVST_FILLOPTIONSPANEL_H
#define TUXPAINTVST_FILLOPTIONSPANEL_H

#include "juce_audio_processors/juce_audio_processors.h"
#include "juce_graphics/juce_graphics.h"
#include "juce_gui_basics/juce_gui_basics.h"

#include "../BinaryDataHeaders/BinaryDataFills.h"
#include "ButtonSelector.h"
#include "OptionsPanel.h"

class FillOptionsPanel : public OptionsPanel
{
public:
    FillOptionsPanel(juce::AudioProcessorValueTreeState& p);
    ~FillOptionsPanel();
    void paint (juce::Graphics& g) override;
    void resized() override;
private:
    ButtonSelector fillSelector;
    enum
    {
        FILL_FLOOD,
        FILL_BRUSH,
        FILL_GRADIENT_LINEAR,
        FILL_GRADIENT_RADIAL,
        FILL_GRADIENT_SHAPED,
        NUM_FILLS
    };

    const std::array<juce::String, NUM_FILLS> fill_names = {
        "Solid",
        "Brush",
        "Linear",
        "Radial",
        "Shaped"
    };

    const std::array<juce::String, NUM_FILLS> fill_tips = {
        "Click to fill an area with a solid color.",
        "Click and drag to fill an area by hand, using a brush.",
        "Click and drag to fill an area with a linear gradient (from the chosen color to transparent).",
        "Click to fill an area with a radial gradient (from the chosen color to transparent).",
        "Click to fill an area with a shaped gradient (from the chosen color to transparent)."
    };

    const std::vector<juce::Image> icons {
        juce::ImageCache::getFromMemory(BinaryDataFills::solid_png, BinaryDataFills::solid_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataFills::brush_png, BinaryDataFills::brush_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataFills::gradient_linear_png, BinaryDataFills::gradient_linear_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataFills::gradient_radial_png, BinaryDataFills::gradient_radial_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataFills::gradient_shaped_png, BinaryDataFills::gradient_shaped_pngSize)
    };
};

#endif //TUXPAINTVST_FILLOPTIONSPANEL_H
