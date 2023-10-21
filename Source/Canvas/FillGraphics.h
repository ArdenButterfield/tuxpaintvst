//
// Created by arden on 8/30/23.
//

#ifndef TUXPAINTVST_FILLGRAPHICS_H
#define TUXPAINTVST_FILLGRAPHICS_H

#include "GraphicsBase.h"
#include "../TuxConstants.h"

class FillGraphics : public GraphicsBase, public juce::AudioProcessorParameter::Listener
{
public:
    FillGraphics(TuxConstants::TuxInternalParameters& p);
    ~FillGraphics();
    void parameterValueChanged (int parameterIndex, float newValue) override;
    void parameterGestureChanged (int parameterIndex, bool gestureIsStarting) override {}

    void doMouseDown(int x, int y) override;
    void doMouseDragged(int x, int y) override;
    void doMouseUp(int x, int y) override {}

private:
    juce::Image imageBeforeFill;
    juce::Point<int> startMouse, currentMouse, previousMouse;
    /* How close colors need to be to match all the time */
    const float COLOR_MATCH_NARROW = 0.04;

    /* How close colors can be to match for a few pixels */
    const float COLOR_MATCH_WIDE = 0.60;

    /* How many pixels can we allow a wide match before stopping? */
    const int WIDE_MATCH_THRESHOLD = 3;

    typedef struct queue_s
    {
        int x, y, y_outside;
    } queue_t;

    std::vector<queue_t> queue;
    std::vector<bool> touchedPixels;
    std::vector<bool> shouldBeFilled;
    juce::Colour fillColor, startingColor;
    int fillMode;

    juce::Colour global_old_colr, global_cur_colr;
    int xMinTouched, yMinTouched, xMaxTouched, yMaxTouched;
    int global_prog_anim;

    void getParamValues();

    void applyFillMask();

    void drawBrushFillSingle(int x, int y);
    void drawBrushFill();

    void simulate_flood_fill(int x, int y);
    void simulate_flood_fill_outside_check(int x, int y, int y_outside);

    TuxConstants::TuxInternalParameters& parameters;
    bool removeFromQueue(int *x, int *y, int *y_outside);
    void doFill(int x, int y);
    [[nodiscard]] bool would_flood_fill(juce::Colour pixelColor) const;
    static float colors_close(juce::Colour c1, juce::Colour c2);
    // juce::Colour blend(juce::Colour draw_colr, juce::Colour old_colr, double pct);

};

#endif //TUXPAINTVST_FILLGRAPHICS_H
