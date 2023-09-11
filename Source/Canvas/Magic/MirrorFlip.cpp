//
// Created by arden on 9/6/23.
//

#include "MirrorFlip.h"

void Magic::MirrorFlip::doOperation(int direction) {
    if (direction == HORIZONTAL)
    {
        for (int yy = 0; yy < canvasImage->getHeight(); ++yy) {

            for (int xx = 0; xx < canvasImage->getWidth(); ++xx)
            {
                canvasData->setPixelColour(xx, yy, snapshotData->getPixelColour(snapshotData->width - xx - 1, yy));
            }
        }
    }
    else if (direction == VERTICAL)
    {
        for (int yy = 0; yy < canvasImage->getHeight(); ++yy) {

            for (int xx = 0; xx < canvasImage->getWidth(); ++xx)
            {
                canvasData->setPixelColour(xx, yy, snapshotData->getPixelColour(xx, snapshotData->height - 1 - yy));
            }
        }
    }
}
