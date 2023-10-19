//
// Created by arden on 7/22/23.
//

#ifndef TUXPAINTVST_CANVAS_H
#define TUXPAINTVST_CANVAS_H

#include "juce_audio_processors/juce_audio_processors.h"
#include "juce_graphics/juce_graphics.h"

#include "../BinaryDataHeaders/BinaryDataUI.h"
#include "../TuxConstants.h"

#include "FillGraphics.h"
#include "EraserGraphics.h"
#include "GraphicsBase.h"
#include "BrushGraphics.h"
#include "MagicGraphics.h"

#include "MusicGuiOverlay.h"

class CanvasPanel : public juce::Component, public juce::AudioProcessorValueTreeState::Listener
{
public:
    CanvasPanel (juce::AudioProcessorValueTreeState& p, juce::Image* c);
    ~CanvasPanel();
    void paint (juce::Graphics& g) override;
    void resized() override;
    juce::Image* getCanvasImage() {return canvas;}
private:
    void mouseDown(const juce::MouseEvent &event) override;
    void mouseDrag(const juce::MouseEvent &event) override;
    void mouseUp(const juce::MouseEvent &event) override;
    void parameterChanged(const juce::String &parameterID, float newValue) override;
    juce::Image* canvas;
    juce::AudioProcessorValueTreeState& parameters;
    FillGraphics fillGraphics;
    EraserGraphics eraserGraphics;
    BrushGraphics brushGraphics;
    MagicGraphics magicGraphics;

    MusicGuiOverlay musicGuiOverlay;

    std::array<GraphicsBase*, TuxConstants::NUM_TOOLS> graphicsTools;
    GraphicsBase* currentGraphics;

    int currentToolIndex;
};

#endif //TUXPAINTVST_CANVAS_H
