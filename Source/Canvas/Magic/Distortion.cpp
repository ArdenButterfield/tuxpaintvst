//
// Created by arden on 9/9/23.
//

#include "Distortion.h"

Magic::Distortion::Distortion() {
    currentMode = MODE_PAINT;
    availableModes = MODE_PAINT;
}
juce::Image Magic::Distortion::getIcon() const
{
    return juce::ImageCache::getFromMemory(BinaryDataMagicIcons::distortion_png, BinaryDataMagicIcons::distortion_pngSize);
}
std::string Magic::Distortion::getName() const
{
    return "Distortion";
}
std::string Magic::Distortion::getDescription() const
{
    return "Click and drag the mouse to cause distortion in your picture.";
}
void Magic::Distortion::click (int x, int y)
{
    drawAlongLine(x, y);
}
void Magic::Distortion::drag (int ox, int oy, int x, int y)
{
    drawLine(ox, oy, x, y);
}
void Magic::Distortion::drawAlongLine (int x, int y)
{
    for (auto yy = std::max(-distortionRadius, -y); yy < std::min(distortionRadius, canvasData->height - y - 1); yy++)
    {
        for (auto xx = std::max(-distortionRadius, -x); xx < std::min(distortionRadius, canvasData->width - x - 1); xx++)
        {
            if (xx * xx + yy * yy < distortionRadius * distortionRadius)
            {
                canvasData->setPixelColour(x + xx, y + yy, snapshotData->getPixelColour(std::clamp(x + xx / 2, 0, snapshotData->width - 1), y + yy));
            }
        }
    }
}
