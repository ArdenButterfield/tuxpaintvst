//
// Created by arden on 8/29/23.
//

#ifndef TUXPAINTVST_BRUSHESOPTIONSPANEL_H
#define TUXPAINTVST_BRUSHESOPTIONSPANEL_H

#include "OptionsPanel.h"

class BrushesOptionsPanel : public OptionsPanel
{
public:
    BrushesOptionsPanel();
    ~BrushesOptionsPanel();
    void paint (juce::Graphics& g) override;
    void resized() override;
private:

};

#endif //TUXPAINTVST_BRUSHESOPTIONSPANEL_H
