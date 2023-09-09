//
// Created by arden on 9/6/23.
//

#include "MirrorFlip.h"

void Magic::MirrorFlip::doOperation(int direction) {
    if (direction == HORIZONTAL)
    {
        for (int yy = 0; yy < canvasImage->getHeight(); ++yy) {

            for (int x_left = 0; x_left < canvasImage->getWidth() / 2; ++x_left)
            {
                auto x_right = canvasImage->getWidth() - 1 - x_left;
                auto temp = canvasImage->getPixelAt(x_right, yy);
                canvasImage->setPixelAt(x_right, yy, canvasImage->getPixelAt(x_left, yy));
                canvasImage->setPixelAt(x_left, yy, temp);
            }
        }
    }
    else if (direction == VERTICAL)
    {
        for (int xx = 0; xx < canvasImage->getWidth(); ++xx)
        {
            for (int y_top = 0; y_top < canvasImage->getHeight() / 2; ++y_top)
            {
                auto y_bottom = canvasImage->getHeight() - 1 - y_top;
                auto temp = canvasImage->getPixelAt (xx, y_bottom);
                canvasImage->setPixelAt (xx, y_bottom, canvasImage->getPixelAt (xx, y_top));
                canvasImage->setPixelAt (xx, y_top, temp);
            }
        }
    }
}
