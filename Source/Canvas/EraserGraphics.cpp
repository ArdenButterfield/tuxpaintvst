//
// Created by arden on 8/30/23.
//

#include "EraserGraphics.h"

EraserGraphics::EraserGraphics(juce::AudioProcessorValueTreeState& p, juce::Colour b) : parameters(p), backgroundColour(b)
{
    parameters.addParameterListener("erasers", this);

    currentEraser = dynamic_cast<juce::AudioParameterChoice*>(parameters.getParameter("erasers"))->getIndex();
}

EraserGraphics::~EraserGraphics()
{
    parameters.removeParameterListener("erasers", this);
}

void EraserGraphics::doMouseDown(int x, int y)
{
    prevX = x;
    prevY = y;
    doErase(x, y);
}

void EraserGraphics::doMouseDragged (int x, int y)
{
    eraseLine(prevX, prevY, x, y);
    prevX = x;
    prevY = y;
}

void EraserGraphics::doErase (int x, int y)
{
    auto g = juce::Graphics(*canvasImage);
    g.setColour(backgroundColour);
    auto sz = calcEraserSize();
    if (currentEraser < TuxConstants::NUM_ERASER_SIZES) {
        // square eraser
        g.fillRect(x - sz, y - sz, sz, sz);
    } else {
        // round eraser
        int yy, xx, hit, n;
        for (yy = 0; yy <= sz; yy++)
        {
            hit = 0;
            for (xx = 0; xx <= sz && hit == 0; xx++)
            {
                n = (xx * xx) + (yy * yy) - ((sz * sz) / 4);

                if (n >= -sz && n <= sz)
                    hit = 1;

                if (hit)
                {
                    g.drawRect(x - xx, y-yy, xx * 2, 1);
                    g.drawRect(x - xx, y + yy, xx * 2, 1);

                }
            }
        }
    }


}
void EraserGraphics::eraseLine (int x1, int y1, int x2, int y2)
{
    int dx, dy, y;
    int orig_x1, orig_y1, orig_x2, orig_y2, tmp;
    float m, b;

    orig_x1 = x1;
    orig_y1 = y1;

    orig_x2 = x2;
    orig_y2 = y2;


    dx = x2 - x1;
    dy = y2 - y1;

    if (dx != 0)
    {
        m = ((float)dy) / ((float)dx);
        b = y1 - m * x1;

        if (x2 >= x1)
            dx = 1;
        else
            dx = -1;


        while (x1 != x2)
        {
            y1 = m * x1 + b;
            y2 = m * (x1 + dx) + b;

            if (y1 > y2)
            {
                for (y = y1; y >= y2; y--)
                    doErase(x1, y);
            }
            else
            {
                for (y = y1; y <= y2; y++)
                    doErase(x1, y);
            }

            x1 = x1 + dx;
        }
    }
    else
    {
        if (y1 > y2)
        {
            y = y1;
            y1 = y2;
            y2 = y;
        }

        for (y = y1; y <= y2; y++)
            doErase(x1, y);
    }


    if (orig_x1 > orig_x2)
    {
        tmp = orig_x1;
        orig_x1 = orig_x2;
        orig_x2 = tmp;
    }

    if (orig_y1 > orig_y2)
    {
        tmp = orig_y1;
        orig_y1 = orig_y2;
        orig_y2 = tmp;
    }
}
void EraserGraphics::parameterChanged (const juce::String& parameterID, float newValue)
{
    currentEraser = dynamic_cast<juce::AudioParameterChoice*>(parameters.getParameter("erasers"))->getIndex();
}
int EraserGraphics::calcEraserSize()
{
    auto sizeind = currentEraser % TuxConstants::NUM_ERASER_SIZES;
    return (TuxConstants::NUM_ERASER_SIZES - 1 - (sizeind)) *
         ((TuxConstants::ERASER_MAX - TuxConstants::ERASER_MIN) / (TuxConstants::NUM_ERASER_SIZES - 1))
           + TuxConstants::ERASER_MIN;

}
