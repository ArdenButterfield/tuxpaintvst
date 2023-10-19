//
// Created by arden on 7/22/23.
//

#ifndef TUXPAINTVST_TUXCONSTANTS_H
#define TUXPAINTVST_TUXCONSTANTS_H

#include "Canvas/Magic/MagicBase.h"
#include "BinaryDataHeaders/BinaryDataBrushes.h"

namespace TuxConstants {

    const int buttonHeight = 48;
    const int buttonWidth = 48;

    /* =========== Tools =========== */
    enum
    {
        TOOL_BRUSH,
        TOOL_STAMP,
        TOOL_LINES,
        TOOL_SHAPES,
        TOOL_TEXT,
        TOOL_MUSIC,
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
        "Music",

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



    /* =========== Brushes =========== */
    enum {
        BRUSH_AA_ROUND_03,
        BRUSH_AA_ROUND_06,
        BRUSH_AA_ROUND_12,
        BRUSH_AA_ROUND_24,
        BRUSH_AA_ROUND_36,
        BRUSH_AA_ROUND_FUZZ,
        BRUSH_AA_ROUND_SEETHRU,
        BRUSH_AA_ROUND_SEETHRU_05,
        BRUSH_AA_ROUND_SEETHRU_10,
        BRUSH_ARROW,
        BRUSH_ARROW_TRIANGLES,
        BRUSH_BLOB,
        BRUSH_CHISLE,
        BRUSH_CUTOUT_SQUARE_DIAMOND,
        BRUSH_CUTOUT_STAR_CIRCLE,
        BRUSH_DIAMOND,
        BRUSH_DOG,
        BRUSH_FLOWER_5,
        BRUSH_FLOWER_5_SMALL,
        BRUSH_FLOWER_6,
        BRUSH_FLOWER_6_SMALL,
        BRUSH_FLOWER_7,
        BRUSH_FOOTPRINTS_HUMAN,
        BRUSH_FOOTPRINTS_HUMAN_SHOES,
        BRUSH_FOOTPRINTS_PAWS,
        BRUSH_HEART,
        BRUSH_HEXAGON,
        BRUSH_INKSPLAT,
        BRUSH_KURONEKO,
        BRUSH_LINES_ANGLED,
        BRUSH_LOZENGE,
        BRUSH_OVAL,
        BRUSH_PENTAGON,
        BRUSH_ROTATING_DASH,
        BRUSH_SLASH_10_LT,
        BRUSH_SLASH_10_RT,
        BRUSH_SLASH_16_LT,
        BRUSH_SLASH_16_RT,
        BRUSH_SLASH_20_LT,
        BRUSH_SLASH_20_RT,
        BRUSH_SPARKLES,
        BRUSH_SPHERE,
        BRUSH_SPIRAL,
        BRUSH_SPLAT,
        BRUSH_SPRAY,
        BRUSH_SQUARE_06,
        BRUSH_SQUARE_12,
        BRUSH_SQUARE_24,
        BRUSH_SQUARE_36,
        BRUSH_SQUARE_FUZZ,
        BRUSH_SQUARE_SEETHRU,
        BRUSH_SQUIRREL,
        BRUSH_STAR,
        BRUSH_TINY,
        BRUSH_TRIANGLE_DOWN,
        BRUSH_TRIANGLE_UP,
        BRUSH_VINE,
        BRUSH_X,
        NUM_BRUSHES
    };

    const std::array<juce::String, NUM_BRUSHES> brush_names = {
        "aa_round_03",
        "aa_round_06",
        "aa_round_12",
        "aa_round_24",
        "aa_round_36",
        "aa_round_fuzz",
        "aa_round_seethru",
        "aa_round_seethru_05",
        "aa_round_seethru_10",
        "arrow",
        "arrow_triangles",
        "blob",
        "chisle",
        "cutout_square_diamond",
        "cutout_star_circle",
        "diamond",
        "dog",
        "flower_5",
        "flower_5_small",
        "flower_6",
        "flower_6_small",
        "flower_7",
        "footprints-human",
        "footprints-human-shoes",
        "footprints-paws",
        "heart",
        "hexagon",
        "inksplat",
        "kuroneko",
        "lines-angled",
        "lozenge",
        "oval",
        "pentagon",
        "rotating_dash",
        "slash_10_lt",
        "slash_10_rt",
        "slash_16_lt",
        "slash_16_rt",
        "slash_20_lt",
        "slash_20_rt",
        "sparkles",
        "sphere",
        "spiral",
        "splat",
        "spray",
        "square_06",
        "square_12",
        "square_24",
        "square_36",
        "square_fuzz",
        "square_seethru",
        "squirrel",
        "star",
        "tiny",
        "triangle_down",
        "triangle_up",
        "vine",
        "x"
    };

    // Generated from .dat files, using getData.py, with some manual edits to brush spacing
    const std::array<int, NUM_BRUSHES> brush_directional = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0};
    const std::array<int, NUM_BRUSHES> brush_rotate = {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    const std::array<int, NUM_BRUSHES> brush_random = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0};
    const std::array<int, NUM_BRUSHES> brush_spacing = {1, 1, 1, 1, 1, 5, 1, 3, 5, 60, 80, 1, 1, 1, 1, 1, 48, 45, 20, 45, 20, 45, 72, 72, 56, 50, 1, 25, 40, 1, 1, 1, 1, 10, 1, 1, 1, 1, 1, 1, 1, 40, 40, 1, 1, 1, 1, 1, 1, 1, 1, 48, 45, 1, 1, 1, 1, 1};
    const std::array<int, NUM_BRUSHES> brush_frames = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 2, 2, 1, 1, -1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, -1, 1, 4, 1, -1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, -1, 1};


    /* =========== Fills =========== */

    enum
    {
        FILL_FLOOD,
        FILL_BRUSH,
        FILL_GRADIENT_LINEAR,
        FILL_GRADIENT_RADIAL,
        NUM_FILLS
    };

    const std::array<juce::String, NUM_FILLS> fill_names = {
        "Solid",
        "Brush",
        "Linear",
        "Radial",
    };

    const std::array<juce::String, NUM_FILLS> fill_tips = {
        "Click to fill an area with a solid color.",
        "Click and drag to fill an area by hand, using a brush.",
        "Click and drag to fill an area with a linear gradient (from the chosen color to transparent).",
        "Click to fill an area with a radial gradient (from the chosen color to transparent).",
    };

    /* =========== Colors =========== */

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

    /* =========== Erasers =========== */

    const int NUM_ERASERS = 16;          /* How many sizes of erasers

    (from ERASER_MIN to _MAX as squares, then again
                                             from ERASER_MIN to _MAX as circles;
        must be a multiple of 2;
        best if a multiple of 4, since selector is 2 buttons across) */

    const int NUM_ERASER_SIZES = (NUM_ERASERS / 2);
    const int ERASER_MIN = 5;            /* Smaller than 5 will not render as a circle! */

    const int ERASER_MAX = 128;

    const juce::Colour backgroundColour = juce::Colour(255,255,255);


}
#endif //TUXPAINTVST_TUXCONSTANTS_H
