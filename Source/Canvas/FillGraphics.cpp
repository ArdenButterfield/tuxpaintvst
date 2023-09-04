//
// Created by arden on 8/30/23.
//

#include "FillGraphics.h"

FillGraphics::FillGraphics(juce::AudioProcessorValueTreeState& p)
     : parameters(p)
{
    parameters.addParameterListener("colors", this);
    parameters.addParameterListener(TuxConstants::tool_names[TuxConstants::TOOL_FILL], this);
    getParamValues();
}

FillGraphics::~FillGraphics()
{
    parameters.removeParameterListener("colors", this);
    parameters.removeParameterListener(TuxConstants::tool_names[TuxConstants::TOOL_FILL], this);

}

void FillGraphics::parameterChanged(const juce::String &parameterID, float newValue)
{
    getParamValues();
}

void FillGraphics::getParamValues()
{
    auto ind = dynamic_cast<juce::AudioParameterChoice*>(parameters.getParameter("colors"))->getIndex();
    fillColor = TuxConstants::default_color_hexes[ind];
    fillMode = dynamic_cast<juce::AudioParameterChoice*>(parameters.getParameter(TuxConstants::tool_names[TuxConstants::TOOL_FILL]))->getIndex();

}

void FillGraphics::doMouseDown (int x, int y)
{
    imageBeforeFill = canvasImage->createCopy();
    startMouse = {x, y};
    currentMouse = {x, y};
    doFill(x, y);
}

void FillGraphics::doMouseDragged (int x, int y)
{
    currentMouse = {x, y};
    if (fillMode == TuxConstants::FILL_GRADIENT_LINEAR) {
        *canvasImage = imageBeforeFill.createCopy();
        applyFillMask();
    }
    // doFill(x,y,juce::Colours::magenta);
}

void FillGraphics::doFill (int x, int y)
{
    if (canvasImage == nullptr) {
        return;
    }
    simulate_flood_fill(x, y);
    applyFillMask();
}
void FillGraphics::applyFillMask()
{
    if (fillMode == TuxConstants::FILL_FLOOD) {
        for (int r = 0; r < canvasImage->getHeight(); ++r) {
            for (int c = 0; c < canvasImage->getWidth(); ++c) {
                if (shouldBeFilled[r * canvasImage->getWidth() + c]) {
                    canvasImage->setPixelAt(c, r, fillColor);
                }

            }
        }
    } else if (fillMode == TuxConstants::FILL_GRADIENT_RADIAL) {
        auto maxX = std::max(currentMouse.getX() - xMinTouched, xMaxTouched - currentMouse.getX());
        auto maxY = std::max(currentMouse.getY() - yMinTouched, yMaxTouched - currentMouse.getY());
        float radius = std::sqrt((float)(maxX * maxX + maxY * maxY));
        for (auto yy = yMinTouched; yy < yMaxTouched; ++yy) {
            for (auto xx = xMinTouched; xx < xMaxTouched; ++xx) {
                if (touchedPixels[yy * canvasImage->getWidth() + xx]) {
                    auto distance = startMouse.getDistanceFrom({xx, yy});
                    if (distance < radius) {
                        float ratio = (float)distance / radius;
                        auto oldPixelColor = canvasImage->getPixelAt(xx, yy);
                        canvasImage->setPixelAt(xx, yy, fillColor.interpolatedWith(oldPixelColor,ratio));
                    }
                }
            }
        }
    }

}
void FillGraphics::simulate_flood_fill (int x, int y)
{
    touchedPixels.resize(canvasImage->getWidth() * canvasImage->getHeight());
    std::fill(touchedPixels.begin(), touchedPixels.end(), false);
    shouldBeFilled.resize(canvasImage->getWidth() * canvasImage->getHeight());
    std::fill(shouldBeFilled.begin(), shouldBeFilled.end(), false);

    int y_outside;
    queue.push_back({x, y, 0});
    startingColor = canvasImage->getPixelAt(x, y);
    xMinTouched = x;
    xMaxTouched = x;
    yMinTouched = y;
    yMaxTouched = y;
    while (removeFromQueue(&x, &y, &y_outside)) {
        simulate_flood_fill_outside_check(x, y, y_outside);
    }
}
bool FillGraphics::removeFromQueue (int* x, int* y, int* y_outside)
{
    if (queue.size() > 0) {
        *x = queue.back().x;
        *y = queue.back().y;
        *y_outside = queue.back().y_outside;
        queue.pop_back();
        return true;
    }
    return false;
}

void FillGraphics::simulate_flood_fill_outside_check (int x, int y, int y_outside)
{
    if (touchedPixels[y * canvasImage->getWidth() + x]) {
        return;
    }

    touchedPixels[y * canvasImage->getWidth() + x] = true;

    xMinTouched = std::min(x, xMinTouched);
    xMaxTouched = std::max(x, xMaxTouched);
    yMinTouched = std::min(y, yMinTouched);
    yMaxTouched = std::max(y, yMaxTouched);

    auto currcolor = canvasImage->getPixelAt(x,y);
    if (would_flood_fill(currcolor)) {
        shouldBeFilled[y * canvasImage->getWidth() + x] = true;
        if (x > 0) {
            queue.push_back({x - 1, y, y_outside});
        }
        if (x < canvasImage->getWidth() - 1) {
            queue.push_back({x + 1, y, y_outside});
        }
        if (y > 0) {
            queue.push_back({x, y - 1, y_outside});
        }
        if (y < canvasImage->getHeight() - 1) {
            queue.push_back({x, y + 1, y_outside});
        }
    }
}

/* Returns how similar colors 'c1' and 'c2' are */
float FillGraphics::colors_close(juce::Colour c1, juce::Colour c2)
{
    if (c1 == c2)
    {
        /* Get it over with quick, if possible! */

        return 0.0;
    }
    else
    {
        float r, g, b;
        r = c1.getFloatRed() - c2.getFloatRed();
        g = c1.getFloatGreen() - c2.getFloatGreen();
        b = c1.getFloatBlue() - c2.getFloatBlue();
        auto score = r * r + b * b + g * g;
        return score;

    }
}
bool FillGraphics::would_flood_fill(juce::Colour cur_colr) const
{
    if (colors_close(cur_colr, startingColor) < COLOR_MATCH_NARROW)
    {
        return true;
    }
    else
    {
        return false;
    }
}
