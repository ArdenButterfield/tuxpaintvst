//
// Created by arden on 10/18/23.
//

#ifndef TUXPAINTVST_MUSICGRAPHICS_H
#define TUXPAINTVST_MUSICGRAPHICS_H

#include "juce_gui_basics/juce_gui_basics.h"
#include "juce_audio_processors/juce_audio_processors.h"

#include "../TuxConstants.h"

class MusicGuiOverlay : public juce::Component, public juce::AudioProcessorParameter::Listener {
public:
    MusicGuiOverlay(TuxConstants::TuxInternalParameters& p, juce::Image& im);
    ~MusicGuiOverlay();
    void mouseDrag(const juce::MouseEvent &event) override;
    void mouseUp(const juce::MouseEvent &event) override;
    void paint(juce::Graphics &g) override;
    void parameterValueChanged (int parameterIndex, float newValue) override;
    void parameterGestureChanged (int parameterIndex, bool gestureIsStarting) override {}
    void setImage(juce::Image& im);
private:
    void getParamValues();

    float paramValue;

    TuxConstants::TuxInternalParameters& parameters;
    juce::Image& image;
};


#endif //TUXPAINTVST_MUSICGRAPHICS_H
