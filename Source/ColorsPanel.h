//
// Created by arden on 7/22/23.
//

#ifndef TUXPAINTVST_COLORSPANEL_H
#define TUXPAINTVST_COLORSPANEL_H

#ifndef gettext_noop
#define gettext_noop(String) String
#endif


#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_graphics/juce_graphics.h>

#include "TuxConstants.h"
#include "ColorButton.h"

typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;


class ColorsPanel
    : public juce::Component,
      public juce::Button::Listener,
      public juce::AudioProcessorValueTreeState::Listener

{
public:
    int NUM_COLORS = 17;

    ColorsPanel(juce::AudioProcessorValueTreeState& p);
    ~ColorsPanel();
    void paint (juce::Graphics& g) override;
    void resized() override;

    void buttonClicked (juce::Button *) override;
    void buttonStateChanged (juce::Button *) override {}

    int colors_rows = 1;
    grid_dims gd_colors;     /* was 17x1 */
private:
    juce::AudioProcessorValueTreeState& parameters;
    void parameterChanged (const juce::String &parameterID, float newValue) override;
    std::unique_ptr<juce::Slider> colorSlider;
    std::unique_ptr<SliderAttachment> colorAttachment;

    juce::OwnedArray<ColorButton> colorButtons;

    int cur_color;
    int old_color;

    enum
    {
        COLOR_BLACK,
        COLOR_DARKGREY,
        COLOR_LIGHTGREY,
        COLOR_WHITE,
        COLOR_RED,
        COLOR_ORANGE,
        COLOR_YELLOW,
        COLOR_LIGHTGREEN,
        COLOR_DARKGREEN,
        COLOR_SKYBLUE,
        COLOR_BLUE,
        COLOR_LAVENDER,
        COLOR_PURPLE,
        COLOR_PINK,
        COLOR_BROWN,
        COLOR_TAN,
        COLOR_BEIGE,
        NUM_DEFAULT_COLORS
    };


    /* Hex codes: */
    const std::array<juce::Colour, NUM_DEFAULT_COLORS> default_color_hexes = {
        juce::Colour{0, 0, 0},                    /* Black */
        juce::Colour{128, 128, 128},              /* Dark grey */
        juce::Colour{192, 192, 192},              /* Light grey */
        juce::Colour{255, 255, 255},              /* White */
        juce::Colour{255, 0, 0},                  /* Red */
        juce::Colour{255, 128, 0},                /* Orange */
        juce::Colour{255, 255, 0},                /* Yellow */
        juce::Colour{160, 228, 128},              /* Light green */
        juce::Colour{33, 148, 70},                /* Dark green */
        juce::Colour{138, 168, 205},              /* Sky blue */
        juce::Colour{50, 100, 255},               /* Blue */
        juce::Colour{186, 157, 255},              /* Lavender */
        juce::Colour{128, 0, 128},                /* Purple */
        juce::Colour{255, 165, 211},              /* Pink */
        juce::Colour{128, 80, 0},                 /* Brown */
        juce::Colour{226, 189, 166},              /* Tan */
        juce::Colour{247, 228, 219}               /* Beige */
    };

    /* Color names: */

    const std::array<juce::String, NUM_DEFAULT_COLORS> default_color_names = {
        // Response to Black (0, 0, 0) color selected
        "Black!",

        // Response to Dark grey (128, 128, 128) color selected
        "Dark grey! Some people spell it \"dark gray\".",

        // Response to Light grey (192, 192, 192) color selected
        "Light grey! Some people spell it \"light gray\".",

        // Response to White (255, 255, 255) color selected
        "White!",

        // Response to Red (255, 0, 0) color selected
        "Red!",

        // Response to Orange (255, 128, 0) color selected
        "Orange!",

        // Response to Yellow (255, 255, 0) color selected
        "Yellow!",

        // Response to Light green (160, 228, 128) color selected
        "Light green!",

        // Response to Dark green (33, 148, 70) color selected
        "Dark green!",

        // Response to "Sky" blue (138, 168, 205) color selected
        "Sky blue!",

        // Response to Blue (50, 100, 255) color selected
        "Blue!",

        // Response to Lavender (186, 157, 255) color selected
        "Lavender!",

        // Response to Purple (128, 0, 128) color selected
        "Purple!",

        // Response to Pink (255, 165, 211) color selected
        "Pink!",

        // Response to Brown (128, 80, 0) color selected
        "Brown!",

        // Response to Tan (226, 189, 166) color selected
        "Tan!",

        // Response to Beige (247, 228, 219) color selected
        "Beige!"
    };


};
#endif //TUXPAINTVST_COLORSPANEL_H
