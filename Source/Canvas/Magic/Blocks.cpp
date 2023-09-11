//
// Created by arden on 9/10/23.
//

#include "Blocks.h"

Magic::Blocks::Blocks()
{
    currentMode = MODE_PAINT;
    availableModes = MODE_PAINT | MODE_FULLSCREEN;
}

std::string Magic::Blocks::getName() const
{
    return "Blocks";
}

std::string Magic::Blocks::getDescription() const
{
    return "Click and drag the mouse around to make the picture blocky.";
}

juce::Image Magic::Blocks::getIcon() const
{
    return juce::ImageCache::getFromMemory(BinaryDataMagicIcons::blocks_png, BinaryDataMagicIcons::blocks_pngSize);
}

void Magic::Blocks::click (int x, int y)
{
    if (currentMode == MODE_PAINT) {
        drag(x, y, x, y);
    } else {
        for (auto yy = 0; yy < canvasImage->getHeight(); yy += EFFECT_REZ) {
            for (auto xx = 0; xx < canvasImage->getWidth(); xx += EFFECT_REZ) {
                drawAlongLine(xx, yy);
            }
        }
    }
}

void Magic::Blocks::drag (int ox, int oy, int x, int y)
{
    if (currentMode == MODE_PAINT) {
        drawLine(ox, oy, x, y);
    }
}

void Magic::Blocks::drawAlongLine (int x, int y)
{
    x = (x / EFFECT_REZ) * EFFECT_REZ;
    y = (y / EFFECT_REZ) * EFFECT_REZ;
    for (auto yy = y - (EFFECT_REZ * 2); yy < y + (EFFECT_REZ * 2); yy = yy + EFFECT_REZ)
    {
        for (auto xx = x - (EFFECT_REZ * 2); xx < x + (EFFECT_REZ * 2); xx = xx + EFFECT_REZ)
        {
            juce::Colour pix[(EFFECT_REZ * EFFECT_REZ)];
            int i = (EFFECT_REZ * EFFECT_REZ);
            bool allSame = true;
            while (i--)
            {
                juce::Colour p_tmp;
                auto pixX = xx + (i / EFFECT_REZ);
                auto pixY = yy + (i % EFFECT_REZ);
                pixX = std::clamp(pixX, 0, snapshotData->width - 1);
                pixY = std::clamp(pixY, 0, snapshotData->height - 1);

                p_tmp = snapshotData->getPixelColour(pixX, pixY);
                pix[i] = p_tmp;
                allSame = (allSame && (pix[0] != p_tmp)) ? false : allSame;
            }
            if (!allSame)
            {
                double r_sum = 0.0;
                double g_sum = 0.0;
                double b_sum = 0.0;

                i = (EFFECT_REZ * EFFECT_REZ);
                while (i--)
                {
                    r_sum += pix[i].getRed();
                    g_sum += pix[i].getGreen();
                    b_sum += pix[i].getBlue();
                }
                juce::Colour avg = {
                    (juce::uint8)(r_sum / (float)(EFFECT_REZ * EFFECT_REZ)),
                    (juce::uint8)(g_sum / (float)(EFFECT_REZ * EFFECT_REZ)),
                    (juce::uint8)(b_sum / (float)(EFFECT_REZ * EFFECT_REZ))
                };
                /* Draw block: */

                graphics->setColour(avg);
                graphics->fillRect(xx, yy, EFFECT_REZ, EFFECT_REZ);
            }
        }
    }

}