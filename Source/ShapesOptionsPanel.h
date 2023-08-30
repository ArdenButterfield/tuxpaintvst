//
// Created by arden on 8/29/23.
//

#ifndef TUXPAINTVST_SHAPESOPTIONSPANEL_H
#define TUXPAINTVST_SHAPESOPTIONSPANEL_H

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_graphics/juce_graphics.h>
#include <juce_gui_basics/juce_gui_basics.h>

#include "OptionsPanel.h"
#include "BinaryDataHeaders/BinaryDataShapes.h"
#include "ButtonSelector.h"

class ShapesOptionsPanel : public OptionsPanel
{
public:
    ShapesOptionsPanel(juce::AudioProcessorValueTreeState& p);
    ~ShapesOptionsPanel();
    void paint (juce::Graphics& g) override;
    void resized() override;
private:
    ButtonSelector shapeSelector;
    enum
    {
        SHAPE_SQUARE,
        SHAPE_SQUARE_FILL,
        SHAPE_RECTANGLE,
        SHAPE_RECTANGLE_FILL,
        SHAPE_CIRCLE,
        SHAPE_CIRCLE_FILL,
        SHAPE_ELLIPSE,
        SHAPE_ELLIPSE_FILL,
        SHAPE_TRIANGLE,
        SHAPE_TRIANGLE_FILL,
        SHAPE_PENTAGON,
        SHAPE_PENTAGON_FILL,
        SHAPE_HEXAGON,
        SHAPE_HEXAGON_FILL,
        SHAPE_HEPTAGON,
        SHAPE_HEPTAGON_FILL,
        SHAPE_OCTAGON,
        SHAPE_OCTAGON_FILL,
        SHAPE_RHOMBUS,
        SHAPE_RHOMBUS_FILL,
        SHAPE_TRIANGLE_STAR,
        SHAPE_TRIANGLE_STAR_FILL,
        SHAPE_RHOMBUS_STAR,
        SHAPE_RHOMBUS_STAR_FILL,
        SHAPE_PENTAGON_STAR,
        SHAPE_PENTAGON_STAR_FILL,
        NUM_SHAPES
    };

    const std::array<juce::String, NUM_SHAPES> shape_names = {
        // Square shape tool (4 equally-lengthed sides at right angles)
        "Square",
        "Square",

        // Rectangle shape tool (4 sides at right angles)
        "Rectangle",
        "Rectangle",

        // Circle shape tool (X radius and Y radius are the same)
        "Circle",
        "Circle",

        // Ellipse shape tool (X radius and Y radius may differ)
        "Ellipse",
        "Ellipse",

        // Triangle shape tool (3 sides)
        "Triangle",
        "Triangle",

        // Pentagon shape tool (5 sides)
        "Pentagon",
        "Pentagon",

        // Hexagon shape tool (6 sides)
        "Hexagon",
        "Hexagon",

        // Heptagon (aka septagon) shape tool (7 sides)
        "Heptagon",
        "Heptagon",

        // Octagon shape tool (8 sides)
        "Octagon",
        "Octagon",

        // Rhombus shape tool (4 sides, not at right angles)
        "Rhombus",
        "Rhombus",

        // Triangle star (3 points star)
        "Star",
        "Star",

        // Rhombus star (4 points star)
        "Star",
        "Star",

        // Pentagon star (5 points star)
        "Star",
        "Star"
    };
    const std::vector<juce::Image> icons {
        juce::ImageCache::getFromMemory(BinaryDataShapes::square_png, BinaryDataShapes::square_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataShapes::square_f_png, BinaryDataShapes::square_f_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataShapes::rectangle_png, BinaryDataShapes::rectangle_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataShapes::rectangle_f_png, BinaryDataShapes::rectangle_f_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataShapes::circle_png, BinaryDataShapes::circle_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataShapes::circle_f_png, BinaryDataShapes::circle_f_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataShapes::oval_png, BinaryDataShapes::oval_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataShapes::oval_f_png, BinaryDataShapes::oval_f_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataShapes::triangle_png, BinaryDataShapes::triangle_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataShapes::triangle_f_png, BinaryDataShapes::triangle_f_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataShapes::pentagon_png, BinaryDataShapes::pentagon_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataShapes::pentagon_f_png, BinaryDataShapes::pentagon_f_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataShapes::hexagon_png, BinaryDataShapes::hexagon_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataShapes::hexagon_f_png, BinaryDataShapes::hexagon_f_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataShapes::heptagon_png, BinaryDataShapes::heptagon_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataShapes::heptagon_f_png, BinaryDataShapes::heptagon_f_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataShapes::octagon_png, BinaryDataShapes::octagon_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataShapes::octagon_f_png, BinaryDataShapes::octagon_f_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataShapes::diamond_png, BinaryDataShapes::diamond_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataShapes::diamond_f_png, BinaryDataShapes::diamond_f_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataShapes::star3p_png, BinaryDataShapes::star3p_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataShapes::star3p_f_png, BinaryDataShapes::star3p_f_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataShapes::star4p_png, BinaryDataShapes::star4p_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataShapes::star4p_f_png, BinaryDataShapes::star4p_f_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataShapes::star5p_png, BinaryDataShapes::star5p_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataShapes::star5p_f_png, BinaryDataShapes::star5p_f_pngSize)
    };


};

#endif //TUXPAINTVST_SHAPESOPTIONSPANEL_H
