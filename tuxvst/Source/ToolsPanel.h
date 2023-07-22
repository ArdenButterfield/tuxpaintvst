//
// Created by arden on 7/22/23.
//
#ifndef TUXPAINTVST_TOOLS_H
#define TUXPAINTVST_TOOLS_H

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_graphics/juce_graphics.h>

#include "TuxConstants.h"


class ToolsPanel : public juce::Component
{
public:
    ToolsPanel();
    ~ToolsPanel();
    void paint (juce::Graphics& g) override;
    void resized() override;
    grid_dims gd_tools;      /* was 2x7 */

private:
};

#endif //TUXPAINTVST_TOOLS_H
