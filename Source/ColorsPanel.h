//
// Created by arden on 7/22/23.
//

#ifndef TUXPAINTVST_COLORSPANEL_H
#define TUXPAINTVST_COLORSPANEL_H

#ifndef gettext_noop
#define gettext_noop(String) String
#endif


#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_graphics/juce_graphics.h>

#include "TuxConstants.h"
#include "ColorButton.h"

typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;


class ColorsPanel
    : public juce::Component,
      public juce::Button::Listener,
      public juce::AudioProcessorValueTreeState::Listener

{
public:
    int NUM_COLORS = 17;

    ColorsPanel(juce::AudioProcessorValueTreeState& p);
    ~ColorsPanel();
    void paint (juce::Graphics& g) override;
    void resized() override;

    void buttonClicked (juce::Button *) override;
    void buttonStateChanged (juce::Button *) override {}

    int colors_rows = 1;
    /* Hex codes: */
private:
    juce::AudioProcessorValueTreeState& parameters;
    void parameterChanged (const juce::String &parameterID, float newValue) override;
    std::unique_ptr<juce::Slider> colorSlider;

    std::unique_ptr<SliderAttachment> colorAttachment;

    juce::OwnedArray<ColorButton> colorButtons;
    int cur_color;

    int old_color;



    /* Color names: */




};
#endif //TUXPAINTVST_COLORSPANEL_H
