//
// Created by arden on 8/30/23.
//

#ifndef TUXPAINTVST_SIZESELECTOR_H
#define TUXPAINTVST_SIZESELECTOR_H

#include "juce_audio_processors/juce_audio_processors.h"
#include "juce_graphics/juce_graphics.h"
#include "juce_gui_basics/juce_gui_basics.h"

#include "../BinaryDataHeaders/BinaryDataUI.h"
#include "../ScrollButton.h"
#include "../ToolButton.h"

class SizeSelector : public juce::Slider
{
public:
    SizeSelector();
    ~SizeSelector();
private:

};

#endif //TUXPAINTVST_SIZESELECTOR_H
