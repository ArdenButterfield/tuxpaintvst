//
// Created by arden on 10/23/23.
//

#include "OscilloscopePanel.h"

OscilloscopePanel::OscilloscopePanel(OscilloscopeData& oscilloscopeData) : data(oscilloscopeData) {
    startTimerHz(30);
}

OscilloscopePanel::~OscilloscopePanel() noexcept
{

}

void OscilloscopePanel::timerCallback()
{
    repaint();
}

void OscilloscopePanel::paint (juce::Graphics& g)
{
    auto p = juce::Path();
    p.startNewSubPath(0,getHeight());
    auto samples = data.getSamples();
    auto incr = (float) getWidth() / (float)(samples->size() - 1);
    float x = 0;
    for (auto s : *(samples)) {
        float y = (getHeight() * 0.5) - (s * getHeight() * 0.5);
        p.lineTo(x, y);
        x += incr;
    }
    g.setColour(juce::Colours::white);
    g.strokePath(p,juce::PathStrokeType(2));
}