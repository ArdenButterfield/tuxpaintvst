//
// Created by arden on 8/30/23.
//

#ifndef TUXPAINTVST_GRAPHICSBASE_H
#define TUXPAINTVST_GRAPHICSBASE_H

#include "juce_audio_processors/juce_audio_processors.h"
#include "juce_graphics/juce_graphics.h"


class GraphicsBase
{
public:
    GraphicsBase() {canvasImage = nullptr;}
    ~GraphicsBase() {}
    virtual void doMouseDown(int x, int y) {}
    virtual void doMouseDragged(int x, int y) {}
    virtual void doMouseUp(int x, int y) {}

    void setImage(juce::Image* im) {canvasImage = im;}
protected:
    juce::Image* canvasImage;
};

#endif //TUXPAINTVST_GRAPHICSBASE_H
