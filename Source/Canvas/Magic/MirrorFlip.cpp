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
        for (int yy = 0; yy < canvasImage->getHeight(); ++yy)
        {
            for (int x_left = 0; x_left < canvasImage->getWidth() / 2; ++x_left)
            {
                auto x_right = canvasImage->getWidth() - 1 - x_left;
                auto temp = canvasImage->getPixelAt (x_right, yy);
                canvasImage->setPixelAt (x_right, yy, canvasImage->getPixelAt (x_left, yy));
                canvasImage->setPixelAt (x_left, yy, temp);
            }
        }
    }
}
