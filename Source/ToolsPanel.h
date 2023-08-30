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

typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;

class ToolsPanel
    : public juce::Component,
      public juce::Button::Listener,
      public juce::AudioProcessorValueTreeState::Listener
{
public:
    ToolsPanel(juce::AudioProcessorValueTreeState& p);
    ~ToolsPanel();
    void paint (juce::Graphics& g) override;
    void resized() override;

    void buttonClicked (juce::Button *) override;
    void buttonStateChanged (juce::Button *) override {}

    grid_dims gd_tools;      /* was 2x7 */

    juce::Rectangle<int> real_tools;

private:

    int cur_tool, old_tool;
    juce::OwnedArray<ToolButton> toolButtons;
    enum
    {
        TOOL_BRUSH,
        TOOL_STAMP,
        TOOL_LINES,
        TOOL_SHAPES,
        TOOL_TEXT,
        TOOL_LABEL,
        TOOL_FILL,
        TOOL_MAGIC,
        TOOL_UNDO,
        TOOL_REDO,
        TOOL_ERASER,
        TOOL_NEW,
        TOOL_OPEN,
        TOOL_SAVE,
        NUM_TOOLS
    };

    int tool_avail[NUM_TOOLS];

    const std::array<juce::Image, NUM_TOOLS> buttonIcons {
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

    const std::array<juce::String, NUM_TOOLS> tool_names = {
        // Freehand painting tool
        "Paint",

        // Stamp tool (aka Rubber Stamps
        "Stamp",

        // Line drawing tool
        "Lines",

        // Shape creation tool (square, circle, etc.
        "Shapes",

        // Text tool
        "Text",

        // Label tool
        "Label",

        // Fill tool
        "Fill",

        // "Magic" effects tools (blur, flip image, etc.
        "Magic",

        // Undo last action
        "Undo",

        // Redo undone action
        "Redo",

        // Eraser tool
        "Eraser",

        // Start a new picture
        "New",

        // Open a saved picture
        "Open",

        // Save the current picture
        "Save"
    };

    /* Some text to write when each tool is selected: */

    const char *const tool_tips[NUM_TOOLS] = {
        // Paint tool instructions
        "Pick a color and a brush shape to draw with.",

        // Stamp tool instructions
        "Pick a picture to stamp around your drawing.",

        // Line tool instructions
        "Click to start drawing a line. Let go to complete it.",

        // Shape tool instructions (defined in "shapes.h"
        "",

        // Text tool instructions
        "Choose a style of text. Click on your drawing and you can start typing. Press [Enter] or [Tab] to complete the text.",

        // Label tool instructions
        "Choose a style of text. Click on your drawing and you can start typing. Press [Enter] or [Tab] to complete the text. By using the selector button and clicking an existing label, you can move it, edit it, and change its text style.",

        // Fill tool instructions (defined in "fill_tools.h"
        "",

        // Magic tool instruction
        "Pick a magical effect to use on your drawing!",

        // Response to 'undo' action
        "Undo!",

        // Response to 'redo' action
        "Redo!",

        // Eraser tool
        "Eraser!",

        // Response to 'start a new image' action
        "Pick a color or picture with which to start a new drawing.",

        // Response to 'open' action (while file dialog is being constructed
        "Open…",

        // Response to 'save' action
        "Your image has been saved!"
    };

    const int numColumns = 2;

    juce::AudioProcessorValueTreeState& parameters;
    void parameterChanged (const juce::String &parameterID, float newValue) override;
    std::unique_ptr<juce::Slider> toolSlider;
    std::unique_ptr<SliderAttachment> toolAttachment;


};

#endif //TUXPAINTVST_TOOLS_H
