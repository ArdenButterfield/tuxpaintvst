//
// Created by arden on 7/22/23.
//

#include "TuxPaint.h"



TuxPaint::TuxPaint(juce::AudioProcessorValueTreeState& p)
    : parameters(p),
      toolsPanel(p),
      colorsPanel(p),
      colorsTitlePanel("Colors"),
      toolsTitlePanel("Tools"),
      shapesOptionsPanel(p),
      fillOptionsPanel(p)
{

    addAndMakeVisible(toolsPanel);
    addAndMakeVisible(canvasPanel);
    addAndMakeVisible(fillOptionsPanel);
    addAndMakeVisible(colorsPanel);
    addAndMakeVisible(infoPanel);
    addAndMakeVisible(colorsTitlePanel);
    addAndMakeVisible(toolsTitlePanel);
}
TuxPaint::~TuxPaint() {

}
void TuxPaint::paint (juce::Graphics& g) {

}
void TuxPaint::resized() {
    /*static SDL_Rect r_canvas;       *//* was 448x376 @ 96,0 *//*
    static SDL_Rect r_tools;        *//* was 96x336 @ 0,40 *//*
    static SDL_Rect r_sfx;
    static SDL_Rect r_toolopt;      *//* was 96x336 @ 544,40 *//*
    static SDL_Rect r_colors;       *//* was 544x48 @ 96,376 *//*
    static SDL_Rect r_ttools;       *//* was 96x40 @ 0,0  (title for tools, "Tools") *//*
    static SDL_Rect r_tcolors;      *//* was 96x48 @ 0,376 (title for colors, "Colors") *//*
    static SDL_Rect r_ttoolopt;     *//* was 96x40 @ 544,0 (title for tool options) *//*
    static SDL_Rect r_tuxarea;      *//* was 640x56 *//*
    static SDL_Rect r_label;
    static SDL_Rect old_dest;
    static SDL_Rect r_tir;          *//* Text input rectangle *//*
    static float render_scale;      *//* Scale factor for the render *//*
    */

    toolsPanel.setBounds(0, 40, 96, 336);
    canvasPanel.setBounds(96,0,448,376);
    fillOptionsPanel.setBounds(544,0,96,376);
    colorsPanel.setBounds(96,376,544,48);
    toolsTitlePanel.setBounds(0,0,96,40);
    colorsTitlePanel.setBounds(0,376,96,48);
}
