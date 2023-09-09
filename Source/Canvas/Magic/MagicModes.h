//
// Created by arden on 9/6/23.
//

#ifndef TUXPAINTVST_MAGICMODES_H
#define TUXPAINTVST_MAGICMODES_H

#endif //TUXPAINTVST_MAGICMODES_H

namespace Magic {
    /* User can paint the tool, freehand */
    /* (Icon: Paint) */
    const int MODE_PAINT = 0x0001;

    /* User can apply effect to entire canvas at once */
    /* (Icon: Fullscreen) */
    const int MODE_FULLSCREEN = 0x0002;

    /* User can paint the tool, freehand -- shows a preview in the meantime */
    /* (Icon: Paint) */
    const int MODE_PAINT_WITH_PREVIEW = 0x0004;

    /* User can click once at different points on the canvas */
    /* (Icon: Paint) */
    const int MODE_ONECLICK = 0x0008;

}