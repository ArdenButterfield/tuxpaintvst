//
// Created by arden on 7/22/23.
//
#ifndef TUXPAINTVST_TOOLS_H
#define TUXPAINTVST_TOOLS_H

#include <iostream>

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_graphics/juce_graphics.h>
#include <juce_gui_basics/juce_gui_basics.h>

#include "BinaryDataHeaders/BinaryDataTools.h"

#include "TuxConstants.h"
#include "ToolButton.h"
#include "NamedToolButton.h"

class ToolsPanel
    : public juce::Component,
      public juce::Button::Listener,
      public juce::AudioProcessorParameter::Listener
{
public:
    ToolsPanel(TuxConstants::TuxInternalParameters& p);
    ~ToolsPanel();
    void paint (juce::Graphics& g) override;
    void resized() override;

    void buttonClicked (juce::Button *) override;
    void buttonStateChanged (juce::Button *) override {}


    juce::Rectangle<int> real_tools;


private:
    int cur_tool, old_tool;
    juce::OwnedArray<ToolButton> toolButtons;

    int tool_avail[TuxConstants::NUM_TOOLS];

    const std::array<juce::Image, TuxConstants::NUM_TOOLS> buttonIcons {
        juce::ImageCache::getFromMemory(BinaryDataTools::brush_png, BinaryDataTools::brush_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataTools::stamp_png, BinaryDataTools::stamp_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataTools::lines_png, BinaryDataTools::lines_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataTools::shapes_png, BinaryDataTools::shapes_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataTools::text_png, BinaryDataTools::text_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataTools::label_png, BinaryDataTools::label_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataTools::fill_png, BinaryDataTools::fill_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataTools::magic_png, BinaryDataTools::magic_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataTools::undo_png, BinaryDataTools::undo_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataTools::redo_png, BinaryDataTools::redo_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataTools::eraser_png, BinaryDataTools::eraser_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataTools::new_png, BinaryDataTools::new_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataTools::open_png, BinaryDataTools::open_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataTools::save_png, BinaryDataTools::save_pngSize),
    };

    const int numColumns = 2;

    TuxConstants::TuxInternalParameters& parameters;
    void parameterValueChanged (int parameterIndex, float newValue) override;
    void parameterGestureChanged (int parameterIndex, bool gestureIsStarting) override {};
};

#endif //TUXPAINTVST_TOOLS_H
