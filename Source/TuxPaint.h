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
#include "OptionPanels/MagicOptionPanel.h"
#include "TitlePanel.h"
#include "ToolsPanel.h"
#include "TuxConstants.h"

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_graphics/juce_graphics.h>

#ifndef TUXPAINTVST_TUXPAINT_H
#define TUXPAINTVST_TUXPAINT_H

#include "TuxConstants.h"
#include "OscilloscopeData.h"
#include "OscilloscopePanel.h"

class TuxPaint : public juce::Component, public juce::AudioProcessorParameter::Listener
{
public:
    TuxPaint(TuxConstants::TuxInternalParameters& p, juce::Image* canvas, OscilloscopeData& oscData);
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
    MagicOptionPanel magicOptionPanel;

    OptionsPanel* currentOptionsPanel{};

    ColorsPanel colorsPanel;
    InfoPanel infoPanel;
    TitlePanel toolsTitlePanel;
    TitlePanel colorsTitlePanel;
    juce::ImageComponent toolTitleBackground;
    juce::ImageComponent colorTitleBackground;

    OscilloscopePanel oscilloscopePanel;

    const int button_w = TuxConstants::buttonWidth;
    const int button_h = TuxConstants::buttonHeight;
    const int color_button_w = 32;
    const int color_button_h = 48;
    void parameterValueChanged (int parameterIndex, float newValue) override;
    void parameterGestureChanged (int parameterIndex, bool gestureIsStarting) override {};

    TuxConstants::TuxInternalParameters& parameters;

};

#endif //TUXPAINTVST_TUXPAINT_H
