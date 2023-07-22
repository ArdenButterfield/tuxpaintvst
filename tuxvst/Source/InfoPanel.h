//
// Created by arden on 7/22/23.
//

#ifndef TUXPAINTVST_INFOPANEL_H
#define TUXPAINTVST_INFOPANEL_H

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_graphics/juce_graphics.h>

class InfoPanel : public juce::Component
{
public:
    InfoPanel();
    ~InfoPanel();
    void paint (juce::Graphics& g) override;
    void resized() override;
};

#endif //TUXPAINTVST_INFOPANEL_H
