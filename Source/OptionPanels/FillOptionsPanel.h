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
    FillOptionsPanel(TuxConstants::TuxInternalParameters& p);
    ~FillOptionsPanel();
    void paint (juce::Graphics& g) override;
    void resized() override;
private:
    ButtonSelector fillSelector;

    const std::vector<juce::Image> icons {
        juce::ImageCache::getFromMemory(BinaryDataFills::solid_png, BinaryDataFills::solid_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataFills::brush_png, BinaryDataFills::brush_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataFills::gradient_linear_png, BinaryDataFills::gradient_linear_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataFills::gradient_radial_png, BinaryDataFills::gradient_radial_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataFills::gradient_shaped_png, BinaryDataFills::gradient_shaped_pngSize)
    };
};

#endif //TUXPAINTVST_FILLOPTIONSPANEL_H
