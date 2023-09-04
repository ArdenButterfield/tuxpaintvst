//
// Created by arden on 8/29/23.
//

#ifndef TUXPAINTVST_BRUSHESOPTIONSPANEL_H
#define TUXPAINTVST_BRUSHESOPTIONSPANEL_H

#include "juce_audio_processors/juce_audio_processors.h"
#include "juce_graphics/juce_graphics.h"
#include "juce_gui_basics/juce_gui_basics.h"
#include "../BinaryDataHeaders/BinaryDataBrushes.h"

#include "ButtonSelector.h"
#include "OptionsPanel.h"


class BrushesOptionsPanel : public OptionsPanel
{
public:
    BrushesOptionsPanel(juce::AudioProcessorValueTreeState& p);
    ~BrushesOptionsPanel();
    void paint (juce::Graphics& g) override;
    void resized() override;
private:
    ButtonSelector brushSelector;

    const std::vector<juce::Image> icons {
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

#endif //TUXPAINTVST_BRUSHESOPTIONSPANEL_H
