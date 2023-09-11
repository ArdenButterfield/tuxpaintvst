//
// Created by arden on 9/5/23.
//

#ifndef TUXPAINTVST_MAGICBASE_H
#define TUXPAINTVST_MAGICBASE_H

#include "juce_audio_processors/juce_audio_processors.h"
#include "juce_graphics/juce_graphics.h"
#include "../../BinaryDataHeaders/BinaryDataMagicIcons.h"
#include "MagicModes.h"

namespace Magic {

    class MagicBase
    {
    public:
        MagicBase() : canvasImage(nullptr), currentMode(0), availableModes(0) {}
        virtual ~MagicBase() = default;
        void setCanvasImage(juce::Image* im) { canvasImage = im; }
        [[nodiscard]] virtual juce::Image getIcon() const {return {};}
        [[nodiscard]] virtual std::string getName() const { return "";}
        [[nodiscard]] virtual std::string getDescription() const {return "";}
        virtual void switchIn() {}
        virtual void switchOut() {}
        virtual void click(int x, int y) {}
        virtual void drag(int ox, int oy, int x, int y) {}
        virtual void release(int x, int y) {}
        virtual bool requireColors() {return false;}
        int getAvailableModes() const {return availableModes;}
        void setMode(int mode) {
            if (mode & availableModes) {
                currentMode = mode;
                std::cout << "set mode to " << mode << "\n";
            }
        }
        int getMode() {
            return currentMode;
        }
        void prepareToDraw() {
            snapshot = canvasImage->createCopy();
            graphics = std::make_unique<juce::Graphics>(*canvasImage);

            canvasData = std::make_unique<juce::Image::BitmapData>(*canvasImage, 0, 0, canvasImage->getWidth(), canvasImage->getHeight(), juce::Image::BitmapData::writeOnly);
            snapshotData = std::make_unique<juce::Image::BitmapData>(snapshot, 0, 0, canvasImage->getWidth(), canvasImage->getHeight(), juce::Image::BitmapData::readOnly);
        }
    protected:
        virtual void drawAlongLine(int x, int y) {}

        void drawLine(int x1, int y1, int x2, int y2) {
            int dx, dy, y;
            float m, b;

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
                            drawAlongLine(x1, y);
                    }
                    else
                    {
                        for (y = y1; y <= y2; y++)
                            drawAlongLine(x1, y);
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
                    drawAlongLine(x1, y);
            }
        }
        juce::Image* canvasImage;
        juce::Image snapshot;
        std::unique_ptr<juce::Image::BitmapData> canvasData;
        std::unique_ptr<juce::Image::BitmapData> snapshotData;
        std::unique_ptr<juce::Graphics> graphics;
        int currentMode{};
        int availableModes{};
    };

}

#endif //TUXPAINTVST_MAGICBASE_H
