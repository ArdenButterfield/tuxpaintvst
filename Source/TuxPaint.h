//
// Created by arden on 7/22/23.
//
#include "Canvas/CanvasPanel.h"
#include "ColorsPanel.h"
#include "InfoPanel.h"
#include "OptionPanels/EraserOptionPanel.h"
#include "OptionPanels/FillOptionsPanel.h"
#include "OptionPanels/OptionsPanel.h"
#include "OptionPanels/ShapesOptionsPanel.h"
#include "OptionPanels/BrushesOptionsPanel.h"
#include "TitlePanel.h"
#include "ToolsPanel.h"
#include "TuxConstants.h"

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_graphics/juce_graphics.h>

#ifndef TUXPAINTVST_TUXPAINT_H
#define TUXPAINTVST_TUXPAINT_H

class TuxPaint : public juce::Component, public juce::AudioProcessorValueTreeState::Listener
{
public:
    TuxPaint(juce::AudioProcessorValueTreeState& p);
    ~TuxPaint();
    void paint (juce::Graphics& g) override;
    void resized() override;

private:
    void updateRightPanel(int toolIndex);

    ToolsPanel toolsPanel;
    CanvasPanel canvasPanel;

    ShapesOptionsPanel shapesOptionsPanel;
    FillOptionsPanel fillOptionsPanel;
    EraserOptionPanel eraserOptionPanel;
    BrushesOptionsPanel brushesOptionsPanel;

    OptionsPanel* currentOptionsPanel;

    ColorsPanel colorsPanel;
    InfoPanel infoPanel;
    TitlePanel toolsTitlePanel;
    TitlePanel colorsTitlePanel;
    juce::ImageComponent toolTitleBackground;
    juce::ImageComponent colorTitleBackground;

    const int button_w = 48;
    const int button_h = 48;
    const int color_button_w = 32;
    const int color_button_h = 48;
    void parameterChanged (const juce::String &parameterID, float newValue) override;

    juce::AudioProcessorValueTreeState& parameters;

};

#endif //TUXPAINTVST_TUXPAINT_H
