//
// Created by arden on 8/30/23.
//

#include "FillGraphics.h"

FillGraphics::FillGraphics(TuxConstants::TuxInternalParameters& p)
     : parameters(p)
{
    parameters.colors.addListener(this);
    parameters.fillOptions.addListener(this);
    getParamValues();
    startTimerHz(30);
    needsRepainting = false;
}

FillGraphics::~FillGraphics()
{
    parameters.colors.removeListener(this);
    parameters.fillOptions.removeListener(this);
}

void FillGraphics::parameterValueChanged (int parameterIndex, float newValue)
{
    getParamValues();
}

void FillGraphics::getParamValues()
{
    auto ind = parameters.colors.getIndex();
    fillColor = TuxConstants::default_color_hexes[ind];
    fillMode = parameters.fillOptions.getIndex();
}

void FillGraphics::doMouseDown (int x, int y)
{
    imageBeforeFill = canvasImage->createCopy();
    startMouse = {x, y};
    currentMouse = {x, y};
    previousMouse = {x, y};
    doFill(x, y);
}

void FillGraphics::doMouseDragged (int x, int y)
{
    currentMouse = {x, y};
    if (fillMode == TuxConstants::FILL_GRADIENT_LINEAR || fillMode == TuxConstants::FILL_BRUSH) {
        // applyFillMask();
        needsRepainting = true;
        // Don't repaint right away, to limit the number of calls per second
    }
    previousMouse = {x, y};
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

void FillGraphics::timerCallback()
{
    if (needsRepainting) {
        applyFillMask();
        needsRepainting = false;
    }
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
    } else if (fillMode == TuxConstants::FILL_GRADIENT_LINEAR) {
        float A, B, C, C1, C2, ratio;
        A = (currentMouse.getX() - startMouse.getX());
        B = (currentMouse.getY() - startMouse.getY());
        C1 = (A * startMouse.getX()) + (B * startMouse.getY());
        C2 = (A * currentMouse.getX()) + (B * currentMouse.getY());
        for (auto yy = yMinTouched; yy < yMaxTouched; ++yy)
        {
            for (auto xx = xMinTouched; xx < xMaxTouched; ++xx)
            {
                if (touchedPixels[yy * canvasImage->getWidth() + xx])
                {
                    /* (h/t David Z on StackOverflow for how to quickly compute this:
                     https://stackoverflow.com/questions/521493/creating-a-linear-gradient-in-2d-array) */
                    C = (A * xx) + (B * yy);

                    if (C < C1)
                    {
                        /* At/beyond the click spot (opposite direction of mouse); solid color */
                        ratio = 0.0;
                    }
                    else if (C >= C2)
                    {
                        /* At/beyond the mouse; completely faded out */
                        ratio = 1.0;
                    }
                    else
                    {
                        /* The actual gradient... */
                        ratio = (C - C1) / (C2 - C1);
                    }

                    auto oldPixelColor = imageBeforeFill.getPixelAt (xx, yy);
                    canvasImage->setPixelAt (xx, yy, fillColor.interpolatedWith (oldPixelColor, ratio));
                }
            }
        }
    } else if (fillMode == TuxConstants::FILL_BRUSH) {
        if (currentMouse == startMouse) {
            drawBrushFillSingle(currentMouse.getX(), currentMouse.getY());
        } else {
            drawBrushFill();
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
    return (colors_close(cur_colr, startingColor) < COLOR_MATCH_NARROW);
}
void FillGraphics::drawBrushFillSingle(int x, int y)
{
    const int brushRadius = 16;
    for (int yy = -brushRadius; yy < brushRadius; ++yy) {
        for (int xx = -brushRadius; xx < brushRadius; ++xx) {
            auto pixX = x + xx;
            auto pixY = y + yy;
            if ((xx * xx + yy * yy < brushRadius * brushRadius) && shouldBeFilled[pixY * canvasImage->getWidth() + pixX]) {
                canvasImage->setPixelAt(pixX, pixY, fillColor);
            }
        }
    }
}
void FillGraphics::drawBrushFill()
{
    int dx, dy;
    int y;
    int orig_x1, orig_y1, orig_x2, orig_y2, tmp;
    float m, b;
    int x1, x2, y1, y2;

    x1 = previousMouse.getX();
    y1 = previousMouse.getY();
    x2 = currentMouse.getX();
    y2 = currentMouse.getY();

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
                    drawBrushFillSingle( x1, y);
            }
            else
            {
                for (y = y1; y <= y2; y++)
                    drawBrushFillSingle(x1, y);
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
            drawBrushFillSingle(x1, y);
    }
}
