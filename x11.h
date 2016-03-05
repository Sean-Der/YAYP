#ifndef X11_H
#define X11_H

#include <stdio.h>
#include <stdlib.h>

#include <X11/Xlib.h>
#include <X11/Xos.h>
#include <X11/Xutil.h>
#include <X11/Intrinsic.h>

void drawPixelMap(void);
GC create_gc(Display* display, Window win);
void draw_pixel(Display* d, GC gc, Window w, Colormap screen_colormap,
		char* color, int x, int y);

#endif
