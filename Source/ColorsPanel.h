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


class ColorsPanel
    : public juce::Component,
      public juce::Button::Listener,
      public juce::AudioProcessorParameter::Listener
{
public:
    int NUM_COLORS = 17;

    ColorsPanel(TuxConstants::TuxInternalParameters& p);
    ~ColorsPanel();
    void paint (juce::Graphics& g) override;
    void resized() override;

    void buttonClicked (juce::Button *) override;
    void buttonStateChanged (juce::Button *) override {}

    int colors_rows = 1;
    /* Hex codes: */
private:
    TuxConstants::TuxInternalParameters& parameters;
    void parameterValueChanged (int parameterIndex, float newValue) override;
    void parameterGestureChanged (int parameterIndex, bool gestureIsStarting) override {};

    juce::OwnedArray<ColorButton> colorButtons;
    int cur_color;

    int old_color;



    /* Color names: */




};
#endif //TUXPAINTVST_COLORSPANEL_H
