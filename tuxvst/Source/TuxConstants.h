//
// Created by arden on 7/22/23.
//

#ifndef TUXPAINTVST_TUXCONSTANTS_H
#define TUXPAINTVST_TUXCONSTANTS_H

typedef struct
{
    int rows, cols;
} grid_dims;


class TuxConstants
{
public:
    static const int WINDOW_WIDTH = 800;
    static const int WINDOW_HEIGHT = 600;

    static const int ORIGINAL_BUTTON_SIZE = 48; /* Original Button Size */
};

#endif //TUXPAINTVST_TUXCONSTANTS_H
