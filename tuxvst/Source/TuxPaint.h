//
// Created by arden on 7/22/23.
//
#include "CanvasPanel.h"
#include "ColorsPanel.h"
#include "InfoPanel.h"
#include "OptionsPanel.h"
#include "ToolsPanel.h"

#include "TuxConstants.h"

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_graphics/juce_graphics.h>

#ifndef TUXPAINTVST_TUXPAINT_H
#define TUXPAINTVST_TUXPAINT_H

class TuxPaint : public juce::Component
{
public:
    ToolsPanel toolsPanel;
    CanvasPanel canvasPanel;
    OptionsPanel optionsPanel;
    ColorsPanel colorsPanel;
    InfoPanel infoPanel;

    TuxPaint();
    ~TuxPaint();
    void paint (juce::Graphics& g) override;
    void resized() override;
private:
    void setScreenLayout();

    int button_w;            /* was 48 */
    int button_h;            /* was 48 */
    int button_size_auto = 0;        /* if the size of buttons should be autocalculated */
    float button_scale = 1.0;      /* scale factor to be applied to the size of buttons */
    int color_button_w;      /* was 32 */
    int color_button_h;      /* was 48 */

    int buttons_tall;        /* promoted to a global variable from setup_normal_screen_layout() */

    /* These are the maximum slots -- some may be unused. */
    grid_dims gd_sfx;

    /* *INDENT-OFF* */
    /* static grid_dims gd_open; *//* was 4x4 */
    /* *INDENT-ON* */

    juce::Rectangle<int> r_ttools;
    juce::Rectangle<int> r_ttoolopt;
    juce::Rectangle<int> r_colors;
    juce::Rectangle<int> r_tcolors;
    juce::Rectangle<int> r_canvas;
    juce::Rectangle<int> r_label;
    juce::Rectangle<int> r_tuxarea;
    juce::Rectangle<int> r_sfx;
    juce::Rectangle<int>  r_tools;
    juce::Rectangle<int>  r_toolopt;

};

#endif //TUXPAINTVST_TUXPAINT_H
