//
// Created by arden on 9/6/23.
//

#ifndef TUXPAINTVST_MAGICOPTIONPANEL_H
#define TUXPAINTVST_MAGICOPTIONPANEL_H

#include "juce_audio_processors/juce_audio_processors.h"
#include "juce_graphics/juce_graphics.h"
#include "juce_gui_basics/juce_gui_basics.h"

#include "ButtonSelector.h"
#include "OptionsPanel.h"
#include "../TuxConstants.h"
#include "../Canvas/Magic/MagicConstants.h"

class MagicOptionPanel : public OptionsPanel, public juce::AudioProcessorValueTreeState::Listener
{
public:
    MagicOptionPanel(juce::AudioProcessorValueTreeState& p);
    ~MagicOptionPanel();
    void paint (juce::Graphics& g) override;
    void resized() override;
private:
    void mouseDown (const juce::MouseEvent& event) override;
    void parameterChanged (const juce::String& parameterID, float newValue) override;
    void setMagicPane(int index);

    std::array<std::vector<juce::Image>, Magic::NUM_MAGIC_TYPES> icons;
    juce::OwnedArray<ButtonSelector> buttonSelectors;
    int currentButtonSelector;

    juce::Rectangle<int> prevButtonBounds;
    juce::Rectangle<int> nextButtonBounds;
    juce::Rectangle<int> magicPaintButtonBounds;
    juce::Rectangle<int> magicFullscreenButtonBounds;

    const juce::Image buttonNav = juce::ImageCache::getFromMemory(BinaryDataUI::btn_nav_png, BinaryDataUI::btn_nav_pngSize);
    const juce::Image prevIcon = juce::ImageCache::getFromMemory(BinaryDataUI::prev_png, BinaryDataUI::prev_pngSize);
    const juce::Image nextIcon = juce::ImageCache::getFromMemory(BinaryDataUI::next_png, BinaryDataUI::next_pngSize);

    const juce::Image buttonUpBackground = juce::ImageCache::getFromMemory (BinaryDataUI::btn_up_png, BinaryDataUI::btn_up_pngSize);
    const juce::Image buttonDownBackground = juce::ImageCache::getFromMemory (BinaryDataUI::btn_down_png, BinaryDataUI::btn_down_pngSize);
    const juce::Image buttonOffBackground = juce::ImageCache::getFromMemory (BinaryDataUI::btn_off_png, BinaryDataUI::btn_off_pngSize);

    const juce::Image magicPaintIcon = juce::ImageCache::getFromMemory(BinaryDataUI::magic_paint_png, BinaryDataUI::magic_paint_pngSize);
    const juce::Image magicFullscreenIcon = juce::ImageCache::getFromMemory(BinaryDataUI::magic_fullscreen_png, BinaryDataUI::magic_fullscreen_pngSize);

    juce::AudioProcessorValueTreeState& parameters;
};

#endif //TUXPAINTVST_MAGICOPTIONPANEL_H
