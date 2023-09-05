//
// Created by arden on 9/4/23.
//

#ifndef TUXPAINTVST_BRUSHGRAPHICS_H
#define TUXPAINTVST_BRUSHGRAPHICS_H

#include "GraphicsBase.h"
#include "../TuxConstants.h"

/* What angle (degrees) is the mouse away from a brush drag, line draw, or stamp placement? */
int brush_rotation(int ctr_x, int ctr_y, int ox, int oy);

class BrushGraphics : public GraphicsBase, public juce::AudioProcessorValueTreeState::Listener
{
public:
    BrushGraphics(juce::AudioProcessorValueTreeState& p);
    ~BrushGraphics();
    void parameterChanged(const juce::String &parameterID, float newValue) override;

    void doMouseDown(int x, int y) override;
    void doMouseDragged(int x, int y) override;
    void doMouseUp(int x, int y) override;
private:
    enum
    {
        BRUSH_DIRECTION_RIGHT,
        BRUSH_DIRECTION_DOWN_RIGHT,
        BRUSH_DIRECTION_DOWN,
        BRUSH_DIRECTION_DOWN_LEFT,
        BRUSH_DIRECTION_LEFT,
        BRUSH_DIRECTION_UP_LEFT,
        BRUSH_DIRECTION_UP,
        BRUSH_DIRECTION_UP_RIGHT,
        BRUSH_DIRECTION_NONE
    };

    juce::AudioProcessorValueTreeState& parameters;
    juce::Point<int> previousMouse;
    juce::Point<int> currentMouse;

    juce::Image currentBrush;
    int currentBrushIndex;
    int brush_counter;
    int brush_frame;

    int img_cur_brush_frame_w;
    int img_cur_brush_w;
    int img_cur_brush_h;


    void makeCurrentBrush();

    juce::Colour currentColor;

    void brush_draw();
    void reset_brush_counter();
    void blit_brush(juce::Graphics& g, int x, int y, int direction, double rotation, int *w, int *h);

    const std::vector<juce::Image> brush_icons {
        juce::ImageCache::getFromMemory(BinaryDataBrushes::aa_round_03_png, BinaryDataBrushes::aa_round_03_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataBrushes::aa_round_06_png, BinaryDataBrushes::aa_round_06_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataBrushes::aa_round_12_png, BinaryDataBrushes::aa_round_12_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataBrushes::aa_round_24_png, BinaryDataBrushes::aa_round_24_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataBrushes::aa_round_36_png, BinaryDataBrushes::aa_round_36_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataBrushes::aa_round_fuzz_png, BinaryDataBrushes::aa_round_fuzz_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataBrushes::aa_round_seethru_05_png, BinaryDataBrushes::aa_round_seethru_05_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataBrushes::aa_round_seethru_10_png, BinaryDataBrushes::aa_round_seethru_10_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataBrushes::aa_round_seethru_png, BinaryDataBrushes::aa_round_seethru_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataBrushes::arrow_png, BinaryDataBrushes::arrow_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataBrushes::arrow_triangles_png, BinaryDataBrushes::arrow_triangles_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataBrushes::blob_png, BinaryDataBrushes::blob_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataBrushes::chisle_png, BinaryDataBrushes::chisle_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataBrushes::cutout_square_diamond_png, BinaryDataBrushes::cutout_square_diamond_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataBrushes::cutout_star_circle_png, BinaryDataBrushes::cutout_star_circle_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataBrushes::diamond_png, BinaryDataBrushes::diamond_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataBrushes::dog_png, BinaryDataBrushes::dog_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataBrushes::flower_5_png, BinaryDataBrushes::flower_5_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataBrushes::flower_5_small_png, BinaryDataBrushes::flower_5_small_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataBrushes::flower_6_png, BinaryDataBrushes::flower_6_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataBrushes::flower_6_small_png, BinaryDataBrushes::flower_6_small_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataBrushes::flower_7_png, BinaryDataBrushes::flower_7_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataBrushes::footprintshuman_png, BinaryDataBrushes::footprintshuman_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataBrushes::footprintshumanshoes_png, BinaryDataBrushes::footprintshumanshoes_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataBrushes::footprintspaws_png, BinaryDataBrushes::footprintspaws_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataBrushes::heart_png, BinaryDataBrushes::heart_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataBrushes::hexagon_png, BinaryDataBrushes::hexagon_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataBrushes::inksplat_png, BinaryDataBrushes::inksplat_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataBrushes::kuroneko_png, BinaryDataBrushes::kuroneko_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataBrushes::linesangled_png, BinaryDataBrushes::linesangled_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataBrushes::lozenge_png, BinaryDataBrushes::lozenge_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataBrushes::oval_png, BinaryDataBrushes::oval_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataBrushes::pentagon_png, BinaryDataBrushes::pentagon_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataBrushes::rotating_dash_png, BinaryDataBrushes::rotating_dash_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataBrushes::slash_10_lt_png, BinaryDataBrushes::slash_10_lt_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataBrushes::slash_10_rt_png, BinaryDataBrushes::slash_10_rt_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataBrushes::slash_16_lt_png, BinaryDataBrushes::slash_16_lt_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataBrushes::slash_16_rt_png, BinaryDataBrushes::slash_16_rt_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataBrushes::slash_20_lt_png, BinaryDataBrushes::slash_20_lt_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataBrushes::slash_20_rt_png, BinaryDataBrushes::slash_20_rt_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataBrushes::sparkles_png, BinaryDataBrushes::sparkles_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataBrushes::sphere_png, BinaryDataBrushes::sphere_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataBrushes::spiral_png, BinaryDataBrushes::spiral_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataBrushes::splat_png, BinaryDataBrushes::splat_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataBrushes::spray_png, BinaryDataBrushes::spray_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataBrushes::square_06_png, BinaryDataBrushes::square_06_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataBrushes::square_12_png, BinaryDataBrushes::square_12_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataBrushes::square_24_png, BinaryDataBrushes::square_24_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataBrushes::square_36_png, BinaryDataBrushes::square_36_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataBrushes::square_fuzz_png, BinaryDataBrushes::square_fuzz_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataBrushes::square_seethru_png, BinaryDataBrushes::square_seethru_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataBrushes::squirrel_png, BinaryDataBrushes::squirrel_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataBrushes::star_png, BinaryDataBrushes::star_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataBrushes::tiny_png, BinaryDataBrushes::tiny_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataBrushes::triangle_down_png, BinaryDataBrushes::triangle_down_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataBrushes::triangle_up_png, BinaryDataBrushes::triangle_up_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataBrushes::vine_png, BinaryDataBrushes::vine_pngSize),
        juce::ImageCache::getFromMemory(BinaryDataBrushes::x_png, BinaryDataBrushes::x_pngSize)
    };
};

#endif //TUXPAINTVST_BRUSHGRAPHICS_H
