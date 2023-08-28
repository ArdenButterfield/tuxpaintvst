//
// Created by arden on 7/22/23.
//

#ifndef TUXPAINTVST_TUXCONSTANTS_H
#define TUXPAINTVST_TUXCONSTANTS_H

typedef struct
{
    int rows, cols;
} grid_dims;

static int grid_hit_gd(const juce::Rectangle<int>& r, unsigned x, unsigned y, grid_dims& gd)
{
    unsigned item_w = r.getWidth() / gd.cols;
    unsigned item_h = r.getHeight() / gd.rows;
    unsigned col = (x - r.getX()) / item_w;
    unsigned row = (y - r.getY()) / item_h;

    if (col >= gd.cols || row >= gd.rows)
        return -1;
    return col + row * gd.cols;
}


class TuxConstants
{
public:
    static const int WINDOW_WIDTH = 800;
    static const int WINDOW_HEIGHT = 600;

    static const int ORIGINAL_BUTTON_SIZE = 48; /* Original Button Size */
};

#endif //TUXPAINTVST_TUXCONSTANTS_H
