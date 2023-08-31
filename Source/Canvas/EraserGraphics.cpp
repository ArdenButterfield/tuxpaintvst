//
// Created by arden on 8/30/23.
//

#include "EraserGraphics.h"

EraserGraphics::EraserGraphics(juce::AudioProcessorValueTreeState& p) : parameters(p)
{
    parameters.addParameterListener("eraser", this);
}

EraserGraphics::~EraserGraphics()
{
    parameters.removeParameterListener("eraser", this);
}

void EraserGraphics::doMouseDown(int x, int y)
{

}

void EraserGraphics::doMouseDragged (int x, int y)
{

}

void EraserGraphics::doErase (int x, int y)
{

}