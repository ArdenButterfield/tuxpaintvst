//
// Created by arden on 7/22/23.
//

#ifndef TUXPAINTVST_CANVAS_H
#define TUXPAINTVST_CANVAS_H

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_graphics/juce_graphics.h>

#include "TuxConstants.h"


class CanvasPanel : public juce::Component
{
public:
    CanvasPanel();
    ~CanvasPanel();
    void paint (juce::Graphics& g) override;
    void resized() override;

private:
};

#endif //TUXPAINTVST_CANVAS_H
