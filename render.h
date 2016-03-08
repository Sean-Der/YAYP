#ifndef RENDER_H
#define RENDER_H

#include <stdio.h>
#include <stdlib.h>

#include <X11/Xlib.h>
#include <X11/Xos.h>
#include <X11/Xutil.h>
#include <X11/Intrinsic.h>

#include "y4m.h"

void renderY4M(Y4M *y4m);

void draw_pixel(Display *d, XImage *xim, Colormap *screen_colormap, unsigned short r, unsigned short g, unsigned short b, int x, int y);

#endif
