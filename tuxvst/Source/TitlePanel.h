//
// Created by arden on 7/22/23.
//

#ifndef TUXPAINTVST_TITLEPANEL_H
#define TUXPAINTVST_TITLEPANEL_H

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_graphics/juce_graphics.h>

#include "TuxConstants.h"


class TitlePanel : public juce::Component
{
public:
    TitlePanel();
    ~TitlePanel();
    void paint (juce::Graphics& g) override;
    void resized() override;

private:
};

#endif //TUXPAINTVST_TITLEPANEL_H
