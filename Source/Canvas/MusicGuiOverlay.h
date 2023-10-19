//
// Created by arden on 10/18/23.
//

#ifndef TUXPAINTVST_MUSICGRAPHICS_H
#define TUXPAINTVST_MUSICGRAPHICS_H

#include "juce_gui_basics/juce_gui_basics.h"
#include "juce_audio_processors/juce_audio_processors.h"

class MusicGuiOverlay : public juce::Component, public juce::AudioProcessorValueTreeState::Listener {
public:
    MusicGuiOverlay(juce::AudioProcessorValueTreeState& p, juce::Image& im);
    ~MusicGuiOverlay();
    void mouseDrag(const juce::MouseEvent &event) override;
    void mouseUp(const juce::MouseEvent &event) override;
    void paint(juce::Graphics &g) override;
    void parameterChanged(const juce::String &parameterID, float newValue) override;
    void setImage(juce::Image& im);
private:
    void getParamValues();

    float paramValue;

    juce::AudioProcessorValueTreeState& parameters;
    juce::Image& image;
};


#endif //TUXPAINTVST_MUSICGRAPHICS_H
