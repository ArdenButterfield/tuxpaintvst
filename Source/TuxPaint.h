//
// Created by arden on 7/22/23.
//
#include "CanvasPanel.h"
#include "ColorsPanel.h"
#include "InfoPanel.h"
#include "OptionsPanel.h"
#include "ToolsPanel.h"
#include "TitlePanel.h"

#include "TuxConstants.h"

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_graphics/juce_graphics.h>

#ifndef TUXPAINTVST_TUXPAINT_H
#define TUXPAINTVST_TUXPAINT_H

class TuxPaint : public juce::Component
{
public:
    ToolsPanel toolsPanel;
    CanvasPanel canvasPanel;
    OptionsPanel optionsPanel;
    ColorsPanel colorsPanel;
    InfoPanel infoPanel;
    TitlePanel toolsTitlePanel;
    TitlePanel optionsTitlePanel;
    TitlePanel colorsTitlePanel;
    juce::ImageComponent toolTitleBackground;
    juce::ImageComponent colorTitleBackground;

    const int button_w = 48;
    const int button_h = 48;
    const int color_button_w = 32;
    const int color_button_h = 48;


    TuxPaint(juce::AudioProcessorValueTreeState& p);
    ~TuxPaint();
    void paint (juce::Graphics& g) override;
    void resized() override;
private:
    juce::AudioProcessorValueTreeState& parameters;

};

#endif //TUXPAINTVST_TUXPAINT_H
