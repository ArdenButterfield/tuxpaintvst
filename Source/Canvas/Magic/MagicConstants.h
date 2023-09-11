//
// Created by arden on 9/6/23.
//

#ifndef TUXPAINTVST_MAGICCONSTANTS_H
#define TUXPAINTVST_MAGICCONSTANTS_H


#include "MagicBase.h"
#include "Flip.h"
#include "Mirror.h"
#include "Distortion.h"
#include "Blocks.h"

namespace Magic {
    /* =========== Magic =========== */

    /* Pre-defined Magic tool grouping codes */
    enum {
        MAGIC_TYPE_DISTORTS,
        MAGIC_TYPE_COLOR_FILTERS,
        MAGIC_TYPE_PICTURE_WARPS,
        MAGIC_TYPE_PAINTING,
        MAGIC_TYPE_PATTERN_PAINTING,
        MAGIC_TYPE_PICTURE_DECORATIONS,
        MAGIC_TYPE_ARTISTIC,
        NUM_MAGIC_TYPES
    };

    const std::array<juce::String, NUM_MAGIC_TYPES> magic_ids = {
        "magicdistorts",
        "magiccolorfilters",
        "magicpicturewarps",
        "magicpainting",
        "magicpatternpainting",
        "magicpicturedecorations",
        "magicartistic"
    };

    const std::array<juce::String, NUM_MAGIC_TYPES> magic_names = {
        "Magic distorts",
        "Magic color filters",
        "Magic picture warps",
        "Magic painting",
        "Magic picture painting",
        "Magic picture decorations",
        "Magic artistic"
    };

    inline Blocks blocks;
    inline Flip flip;
    inline Mirror mirror;
    inline Distortion distortion;

    const std::array<const std::vector<MagicBase*>, NUM_MAGIC_TYPES> magicEffects = {
        std::vector<MagicBase*>({&blocks, &distortion}),
        std::vector<MagicBase*>({&mirror, &flip}),
        std::vector<MagicBase*>({&mirror, &flip}),
        std::vector<MagicBase*>({&mirror, &flip}),
        std::vector<MagicBase*>({&mirror, &flip}),
        std::vector<MagicBase*>({&mirror, &flip}),
        std::vector<MagicBase*>({&mirror, &flip}),
    };

    inline MagicBase* getCurrentMagicEffect(juce::AudioProcessorValueTreeState& parameters) {
        auto magictype = (dynamic_cast<juce::AudioParameterChoice*>(parameters.getParameter("magictype")))->getIndex();
        auto effectindex = (dynamic_cast<juce::AudioParameterChoice*>(parameters.getParameter(magic_ids[magictype])))->getIndex();
        return magicEffects[magictype][effectindex];

    }
}

#endif //TUXPAINTVST_MAGICCONSTANTS_H
