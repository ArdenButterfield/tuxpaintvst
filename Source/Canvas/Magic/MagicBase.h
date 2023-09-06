//
// Created by arden on 9/5/23.
//

#ifndef TUXPAINTVST_MAGICBASE_H
#define TUXPAINTVST_MAGICBASE_H

#include "juce_audio_processors/juce_audio_processors.h"
#include "juce_graphics/juce_graphics.h"

#include "../../TuxConstants.h"

class MagicBase
{
public:
    MagicBase() {}
    ~MagicBase() {}
    void setCanvasImage(juce::Image im) {}
    juce::Image* getIcon() {return nullptr;}
    std::string getName() {return "";}
    int getGroup() {return 0;}
    std::string getDescription() {return "";}
    void switchIn() {}
    void switchOut() {}
    void click(int mode, int x, int y) {}
    void drag(int ox, int oy, int x, int y) {}
    void release(int x, int y) {}
    bool requireColors() {return false;}

private:
    juce::Image* canvasImage;
};

#endif //TUXPAINTVST_MAGICBASE_H
