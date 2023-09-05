//
// Created by arden on 9/4/23.
//

#include "BrushGraphics.h"

/* What angle (degrees) is the mouse away from a brush drag, line draw, or stamp placement? */
int brush_rotation(int ctr_x, int ctr_y, int ox, int oy)
{
    return (int)(atan2(oy - ctr_y, ox - ctr_x) * 180 / 3.14159);
}


BrushGraphics::BrushGraphics (juce::AudioProcessorValueTreeState& p) : parameters(p)
{
    parameters.addParameterListener("brushes", this);
    parameters.addParameterListener("colors", this);
    currentBrushIndex = dynamic_cast<juce::AudioParameterChoice*>(parameters.getParameter("brushes"))->getIndex();
    currentColor = TuxConstants::default_color_hexes[dynamic_cast<juce::AudioParameterChoice*>(parameters.getParameter("colors"))->getIndex()];
    makeCurrentBrush();
}

BrushGraphics::~BrushGraphics()
{
    parameters.removeParameterListener("colors", this);
    parameters.removeParameterListener("brushes", this);

}

void BrushGraphics::parameterChanged (const juce::String& parameterID, float newValue)
{
    currentColor = TuxConstants::default_color_hexes[dynamic_cast<juce::AudioParameterChoice*>(parameters.getParameter("colors"))->getIndex()];

    currentBrushIndex = dynamic_cast<juce::AudioParameterChoice*>(parameters.getParameter("brushes"))->getIndex();
    makeCurrentBrush();
}

void BrushGraphics::makeCurrentBrush()
{
    currentBrush = brush_icons[currentBrushIndex].createCopy();
    for (int y = 0; y < currentBrush.getHeight(); ++y) {
        for (int x = 0; x < currentBrush.getWidth(); ++x) {
            auto pix = currentBrush.getPixelAt(x, y);
            if ((pix.getRed() == pix.getGreen()) && (pix.getRed() == pix.getBlue())) {
                currentBrush.setPixelAt(x,y,currentColor.withAlpha(pix.getFloatAlpha()));
            } else {
                currentBrush.setPixelAt(x,y,currentColor.interpolatedWith(pix,0.5));
            }
        }
    }
}


void BrushGraphics::doMouseDown (int x, int y)
{
    previousMouse.setXY(x, y);
    reset_brush_counter();
}

void BrushGraphics::doMouseDragged (int x, int y)
{
    currentMouse.setXY(x, y);
    brush_draw();

    previousMouse.setXY(x, y);
}

void BrushGraphics::doMouseUp (int x, int y)
{
    currentMouse.setXY(x, y);

    brush_draw();
}

void BrushGraphics::brush_draw()
{
    auto g = juce::Graphics(*canvasImage);

    brush_frame = 0;
    int x1, y1, x2, y2;
    x1 = previousMouse.getX();  y1 = previousMouse.getY();
    x2 = currentMouse.getX();   y2 = currentMouse.getY();

    int dx, dy, y, frame_w, w, h, sz;
    int orig_x1, orig_y1, orig_x2, orig_y2, tmp;
    int direction;
    float m, b;
    double r;

    orig_x1 = x1;
    orig_y1 = y1;

    orig_x2 = x2;
    orig_y2 = y2;


    frame_w = currentBrush.getWidth() / abs(TuxConstants::brush_frames[currentBrushIndex]);
    w = frame_w / (TuxConstants::brush_directional[currentBrushIndex] ? 3 : 1);
    h = currentBrush.getHeight() / (TuxConstants::brush_directional[currentBrushIndex] ? 3 : 1);

    x1 = x1 - (w >> 1);
    y1 = y1 - (h >> 1);

    x2 = x2 - (w >> 1);
    y2 = y2 - (h >> 1);


    direction = BRUSH_DIRECTION_NONE;
    r = -1.0;
    if (TuxConstants::brush_directional[currentBrushIndex] || TuxConstants::brush_rotate[currentBrushIndex])
    {
        r = brush_rotation(x1, y1, x2, y2);

        if (TuxConstants::brush_directional[currentBrushIndex])
        {
            r = r + 22.0;
            if (r < 0.0)
                r = r + 360.0;
            if (x1 != x2 || y1 != y2)
                direction = (r / 45.0);
        }
        else
        {
            r = 270.0 - r;
        }
    }


    dx = x2 - x1;
    dy = y2 - y1;

    if (dx != 0)
    {
        m = ((float)dy) / ((float)dx);
        b = y1 - m * x1;

        if (x2 >= x1)
            dx = 1;
        else
            dx = -1;


        while (x1 != x2)
        {
            y1 = m * x1 + b;
            y2 = m * (x1 + dx) + b;

            if (y1 > y2)
            {
                for (y = y1; y >= y2; y--)
                    blit_brush(g, x1, y, direction, r, &w, &h);
            }
            else
            {
                for (y = y1; y <= y2; y++)
                    blit_brush(g, x1, y, direction, r, &w, &h);
            }

            x1 = x1 + dx;
        }
    }
    else
    {
        if (y1 > y2)
        {
            y = y1;
            y1 = y2;
            y2 = y;
        }

        for (y = y1; y <= y2; y++)
            blit_brush(g, x1, y, direction, r, &w, &h);
    }

    if (orig_x1 > orig_x2)
    {
        tmp = orig_x1;
        orig_x1 = orig_x2;
        orig_x2 = tmp;
    }

    if (orig_y1 > orig_y2)
    {
        tmp = orig_y1;
        orig_y1 = orig_y2;
        orig_y2 = tmp;
    }
}

/**
 * Reset the brush counter, such that the next attempt to draw something
 * is either (a) guaranteed to do so, regardless of the brush's spacing
 * (for non-rotational brushes), or (b) requires the user to have moved
 * far enough to get a good idea of the angle they're drawing
 * (for rotational brushes).
 */

void BrushGraphics::reset_brush_counter()
{
    if (TuxConstants::brush_directional[currentBrushIndex]) {
        brush_counter = 0;
    } else {
        brush_counter = 9999;
    }
}

void BrushGraphics::blit_brush (juce::Graphics& g, int x, int y, int direction, double rotation, int* w, int* h)
{
    juce::Rectangle<int> src, dest;

    brush_counter++;
    if (brush_counter >= TuxConstants::brush_spacing[currentBrushIndex])
    {
        brush_counter = 0;

        if (TuxConstants::brush_frames[currentBrushIndex] >= 0)
        {
            brush_frame++;
            if (brush_frame >= TuxConstants::brush_frames[currentBrushIndex])
                brush_frame = 0;
        }
        else
        {
            int old_brush_frame = brush_frame;

            do
            {
                brush_frame = rand() % abs(TuxConstants::brush_frames[currentBrushIndex]);
            }
            while (brush_frame == old_brush_frame);
        }

        dest.setX(x);
        dest.setY(y);

        // if (TuxConstants::brush_directional[currentBrushIndex]) TODO: bring back
        if (false)
        {
/*            if (direction == BRUSH_DIRECTION_UP_LEFT ||
                direction == BRUSH_DIRECTION_UP || direction == BRUSH_DIRECTION_UP_RIGHT)
            {
                src.y = 0;
            }
            else if (direction == BRUSH_DIRECTION_LEFT ||
                     direction == BRUSH_DIRECTION_NONE || direction == BRUSH_DIRECTION_RIGHT)
            {
                src.y = img_cur_brush_h;
            }
            else if (direction == BRUSH_DIRECTION_DOWN_LEFT ||
                     direction == BRUSH_DIRECTION_DOWN || direction == BRUSH_DIRECTION_DOWN_RIGHT)
            {
                src.y = img_cur_brush_h << 1;
            }

            if (direction == BRUSH_DIRECTION_UP_LEFT ||
                direction == BRUSH_DIRECTION_LEFT || direction == BRUSH_DIRECTION_DOWN_LEFT)
            {
                src.x = brush_frame * img_cur_brush_frame_w;
            }
            else if (direction == BRUSH_DIRECTION_UP ||
                     direction == BRUSH_DIRECTION_NONE || direction == BRUSH_DIRECTION_DOWN)
            {
                src.x = brush_frame * img_cur_brush_frame_w + img_cur_brush_w;
            }
            else if (direction == BRUSH_DIRECTION_UP_RIGHT ||
                     direction == BRUSH_DIRECTION_RIGHT || direction == BRUSH_DIRECTION_DOWN_RIGHT)
            {
                src.x = brush_frame * img_cur_brush_frame_w + (img_cur_brush_w << 1);
            }*/
        }
        else
        {
            src.setX(brush_frame * currentBrush.getWidth());
            src.setY(0);
        }

        src.setWidth(currentBrush.getWidth());
        src.setHeight(currentBrush.getHeight());
        dest.setWidth(src.getWidth());
        dest.setHeight(src.getHeight());
        // if (TuxConstants::brush_rotate[currentBrushIndex] && rotation != -1.0 /* only if we're moving */ )
        if (false)
        {
/*
            SDL_Surface *rotated_brush;

            */
/* TODO: Cache these; discard them when the user changes the brush or alters its color *//*


            rotated_brush = NULL;

            if (img_cur_brush_frames != 1)
            {
                SDL_Surface *brush_frame_surf;

                brush_frame_surf =
                    SDL_CreateRGBSurface(img_cur_brush->flags,
                        src.w,
                        src.h,
                        img_cur_brush->format->BitsPerPixel,
                        img_cur_brush->format->Rmask,
                        img_cur_brush->format->Gmask,
                        img_cur_brush->format->Bmask, img_cur_brush->format->Amask);
                if (brush_frame_surf != NULL)
                {
                    */
/* 2021/09/28 SDL(2)_gfxBlitRGBA() is not available in the SDL2_gfx library, using plain SDL_BlitSurface() instead. Pere
             SDL_gfxBlitRGBA(img_cur_brush, &src, brush_frame_surf, NULL); *//*

                    SDL_BlitSurface(img_cur_brush, &src, brush_frame_surf, NULL);
                    rotated_brush = rotozoomSurface(brush_frame_surf, rotation, 1.0, SMOOTHING_ON);
                    SDL_FreeSurface(brush_frame_surf);
                }
            }
            else
            {
                rotated_brush = rotozoomSurface(img_cur_brush, rotation, 1.0, SMOOTHING_ON);
            }

            if (rotated_brush != NULL)
            {
                src.x = 0;
                src.y = 0;
                src.w = rotated_brush->w;
                src.h = rotated_brush->h;

                dest.x = dest.x - (img_cur_brush_w >> 1) + (rotated_brush->w >> 1);
                dest.y = dest.y - (img_cur_brush_h >> 1) + (rotated_brush->h >> 1);
                dest.w = rotated_brush->w;
                dest.h = rotated_brush->h;

                SDL_BlitSurface(rotated_brush, &src, canvas, &dest);

                SDL_FreeSurface(rotated_brush);
            }
*/
        }
        else
        {
            g.drawImage(currentBrush,
                dest.getX(),
                dest.getY(),
                dest.getWidth(),
                dest.getHeight(),
                src.getX(),
                src.getY(),
                src.getWidth(),
                src.getHeight());
        }
    }

    *w = src.getWidth();
    *h = src.getHeight();
}
