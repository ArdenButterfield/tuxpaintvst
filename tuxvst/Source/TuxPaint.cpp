//
// Created by arden on 7/22/23.
//

#include "TuxPaint.h"



TuxPaint::TuxPaint() {
    addAndMakeVisible(toolsPanel);
    addAndMakeVisible(canvasPanel);
    addAndMakeVisible(optionsPanel);
    addAndMakeVisible(colorsPanel);
    addAndMakeVisible(infoPanel);
}
TuxPaint::~TuxPaint() {

}
void TuxPaint::paint (juce::Graphics& g) {

}

void TuxPaint::setScreenLayout() {
    button_w = 48 * button_scale;
    button_h = 48 * button_scale;

    r_ttools = juce::Rectangle<int>(0,0, toolsPanel.gd_tools.cols * button_w,40 * button_scale);

    r_ttoolopt.setWidth( optionsPanel.gd_toolopt.cols * button_w);
    r_ttoolopt.setHeight(40 * button_scale);
    r_ttoolopt.setX(TuxConstants::WINDOW_WIDTH - r_ttoolopt.getWidth());
    r_ttoolopt.setY(0);


    r_colors.setHeight(48 * button_scale * colorsPanel.gd_colors.rows);
    color_button_h = r_colors.getHeight() /colorsPanel.gd_colors.rows;
    r_tcolors.setHeight(r_colors.getHeight());

    r_tcolors.setX(0);
    r_tcolors.setWidth(toolsPanel.gd_tools.cols * button_w);
    r_colors.setX(r_tcolors.getWidth());
    r_colors.setWidth(TuxConstants::WINDOW_WIDTH - r_tcolors.getWidth());

    color_button_w = r_colors.getWidth() / colorsPanel.gd_colors.cols;

    /* This would make it contain _just_ the color spots,
     without any leftover bit on the end. Hmmm... */
    /* r_colors.setWidth(color_button_w * gd_colors.cols; */

    r_canvas.setX(toolsPanel.gd_tools.cols * button_w);
    r_canvas.setY(0);
    r_canvas.setWidth(TuxConstants::WINDOW_WIDTH - (toolsPanel.gd_tools.cols + optionsPanel.gd_toolopt.cols) * button_w);

    r_tuxarea.setX(0);
    r_tuxarea.setWidth(TuxConstants::WINDOW_WIDTH);

    /* need 56 minimum for the Tux area */
    buttons_tall = (TuxConstants::WINDOW_HEIGHT - r_ttoolopt.getHeight() - 56 * button_scale - r_colors.getHeight()) / button_h;
    if (buttons_tall < 5)
    {
        fprintf(stderr,
            "Button size '%d' with window size '%dx%d' is not reasonable (not tall enough).\n",
            button_w, TuxConstants::WINDOW_WIDTH, TuxConstants::WINDOW_HEIGHT);
        // set_max_buttonscale();
//        setup_normal_screen_layout();
    }

    if (r_canvas.getWidth() < button_w * 9)
    {
        fprintf(stderr,
            "Button size '%d' with window size '%dx%d' is not reasonable (not wide enough).\n",
            button_w, TuxConstants::WINDOW_WIDTH, TuxConstants::WINDOW_HEIGHT);
//        set_max_buttonscale();
//        setup_normal_screen_layout();
    }

    toolsPanel.gd_tools.rows = buttons_tall;
    optionsPanel.gd_toolopt.rows = buttons_tall;

    r_canvas.setHeight(r_ttoolopt.getHeight() + buttons_tall * button_h);

    r_label = r_canvas;

    r_colors.setY(r_canvas.getHeight() + r_canvas.getY());
    r_tcolors.setY(r_canvas.getHeight() + r_canvas.getY());

    r_tuxarea.setY(r_colors.getY() + r_colors.getHeight());
    r_tuxarea.setHeight(TuxConstants::WINDOW_HEIGHT - r_tuxarea.getY());

    r_sfx.setX(r_tuxarea.getX());
    r_sfx.setY(r_tuxarea.getY());
    r_sfx.setWidth(button_w);           /* Two half-sized buttons across */
    r_sfx.setHeight(button_h >> 1);      /* One half-sized button down */

    gd_sfx.rows = 1;
    gd_sfx.cols = 2;

    r_tools.setX(0);
    r_tools.setY(r_ttools.getHeight() + r_ttools.getY());
    r_tools.setWidth(toolsPanel.gd_tools.cols * button_w);
    r_tools.setHeight(toolsPanel.gd_tools.rows * button_h);

    r_toolopt.setWidth(optionsPanel.gd_toolopt.cols * button_w);
    r_toolopt.setHeight(optionsPanel.gd_toolopt.rows * button_h);
    r_toolopt.setX(TuxConstants::WINDOW_WIDTH - r_ttoolopt.getWidth());
    r_toolopt.setY(r_ttoolopt.getHeight() + r_ttoolopt.getY());

    /* TODO: dialog boxes */
}

void TuxPaint::resized() {
    setScreenLayout();
    toolsPanel.setBounds(r_tools);
    canvasPanel.setBounds(r_canvas);
    optionsPanel.setBounds(r_toolopt);
    colorsPanel.setBounds(r_colors);
    // optionsPanel.setBounds()
}
