//
// Created by arden on 8/30/23.
//

#ifndef TUXPAINTVST_ERASEROPTIONPANEL_H
#define TUXPAINTVST_ERASEROPTIONPANEL_H

#include "juce_audio_processors/juce_audio_processors.h"
#include "juce_graphics/juce_graphics.h"
#include "juce_gui_basics/juce_gui_basics.h"

#include "ButtonSelector.h"
#include "OptionsPanel.h"

std::vector<juce::Image> makeIcons(const int numErasers);

class EraserOptionPanel : public OptionsPanel
{
public:
    EraserOptionPanel(juce::AudioProcessorValueTreeState& p);
    ~EraserOptionPanel();
    void paint (juce::Graphics& g) override;
    void resized() override;
private:
    const int NUM_ERASERS = 16;          /* How many sizes of erasers

                                   (from ERASER_MIN to _MAX as squares, then again
                                   from ERASER_MIN to _MAX as circles;
                                   must be a multiple of 2;
                                   best if a multiple of 4, since selector is 2 buttons across) */

    const int NUM_ERASER_SIZES = (NUM_ERASERS / 2);
    const int ERASER_MIN = 5;            /* Smaller than 5 will not render as a circle! */

    const int ERASER_MAX = 128;

    const std::vector<juce::Image> icons;
    ButtonSelector eraserSelector;
};

#endif //TUXPAINTVST_ERASEROPTIONPANEL_H
