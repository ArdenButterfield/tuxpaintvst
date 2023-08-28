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



class ColorsPanel : public juce::Component
{
public:
    int NUM_COLORS = 17;

    ColorsPanel();
    ~ColorsPanel();
    void paint (juce::Graphics& g) override;
    void resized() override;
    int colors_rows = 1;
    grid_dims gd_colors;     /* was 17x1 */
private:


    std::vector<std::array<int, 3>> color_hexes = {
        {0, 0, 0},                    /* Black */
        {128, 128, 128},              /* Dark grey */
        {192, 192, 192},              /* Light grey */
        {255, 255, 255},              /* White */
        {255, 0, 0},                  /* Red */
        {255, 128, 0},                /* Orange */
        {255, 255, 0},                /* Yellow */
        {160, 228, 128},              /* Light green */
        {33, 148, 70},                /* Dark green */
        {138, 168, 205},              /* Sky blue */
        {50, 100, 255},               /* Blue */
        {186, 157, 255},              /* Lavender */
        {128, 0, 128},                /* Purple */
        {255, 165, 211},              /* Pink */
        {128, 80, 0},                 /* Brown */
        {226, 189, 166},              /* Tan */
        {247, 228, 219}               /* Beige */
    };

    std::vector<std::string> color_names = {
        // Response to Black (0, 0, 0) color selected
        gettext_noop("Black!"),

        // Response to Dark grey (128, 128, 128) color selected
        gettext_noop("Dark grey! Some people spell it “dark gray”."),

        // Response to Light grey (192, 192, 192) color selected
        gettext_noop("Light grey! Some people spell it “light gray”."),

        // Response to White (255, 255, 255) color selected
        gettext_noop("White!"),

        // Response to Red (255, 0, 0) color selected
        gettext_noop("Red!"),

        // Response to Orange (255, 128, 0) color selected
        gettext_noop("Orange!"),

        // Response to Yellow (255, 255, 0) color selected
        gettext_noop("Yellow!"),

        // Response to Light green (160, 228, 128) color selected
        gettext_noop("Light green!"),

        // Response to Dark green (33, 148, 70) color selected
        gettext_noop("Dark green!"),

        // Response to "Sky" blue (138, 168, 205) color selected
        gettext_noop("Sky blue!"),

        // Response to Blue (50, 100, 255) color selected
        gettext_noop("Blue!"),

        // Response to Lavender (186, 157, 255) color selected
        gettext_noop("Lavender!"),

        // Response to Purple (128, 0, 128) color selected
        gettext_noop("Purple!"),

        // Response to Pink (255, 165, 211) color selected
        gettext_noop("Pink!"),

        // Response to Brown (128, 80, 0) color selected
        gettext_noop("Brown!"),

        // Response to Tan (226, 189, 166) color selected
        gettext_noop("Tan!"),

        // Response to Beige (247, 228, 219) color selected
        gettext_noop("Beige!")
    };

};
#endif //TUXPAINTVST_COLORSPANEL_H
