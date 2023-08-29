//
// Created by arden on 7/22/23.
//

#ifndef TUXPAINTVST_TITLEPANEL_H
#define TUXPAINTVST_TITLEPANEL_H

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_graphics/juce_graphics.h>

#include "BinaryDataHeaders/BinaryDataUI.h"
#include "BinaryDataHeaders/BinaryDataFonts.h"
#include "TuxConstants.h"


class TitlePanel : public juce::Component
{
public:
    TitlePanel(juce::String _name);
    ~TitlePanel();
    void paint (juce::Graphics& g) override;
    void resized() override;

private:
    juce::Typeface::Ptr defaultTypeface;
    juce::Font titleFont;

    juce::String name;
    juce::Label titleLabel;

    juce::ImageComponent background;

    const juce::Image titleBackground = juce::ImageCache::getFromMemory(BinaryDataUI::title_png, BinaryDataUI::title_pngSize);
    const juce::Image titleBackgroundBig = juce::ImageCache::getFromMemory(BinaryDataUI::title_large_png, BinaryDataUI::title_large_pngSize);

};

#endif //TUXPAINTVST_TITLEPANEL_H
