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
    EraserOptionPanel(TuxConstants::TuxInternalParameters& p);
    ~EraserOptionPanel();
    void paint (juce::Graphics& g) override;
    void resized() override;
private:

    const std::vector<juce::Image> icons;
    ButtonSelector eraserSelector;
};

#endif //TUXPAINTVST_ERASEROPTIONPANEL_H
