#include "x11.h"

void drawPixelMap(void) {
    Display* d;
    XEvent e;
    int s;
    if ((d = XOpenDisplay(NULL)) == NULL) {
	fprintf(stderr, "Cannot open display\n");
	exit(1);
    }

    s = DefaultScreen(d);
    Window w = XCreateSimpleWindow(d, RootWindow(d, s), 0, 0, 100, 100, 1,
				   BlackPixel(d, s), WhitePixel(d, s));
    GC gc = create_gc(d, w);
    Colormap screen_colormap = DefaultColormap(d, s);

    XSelectInput(d, w, ExposureMask | KeyPressMask);
    XMapWindow(d, w);

    while (1) {
	XNextEvent(d, &e);

	if (e.type == Expose) {
	    for (int x = 0; x <= 300; x++) {
		for (int y = 0; y <= 300; y++) {
		    draw_pixel(d, gc, w, screen_colormap,
			       (y % 2) ? "red" : "green", x, y);
		}
	    }
	}

	// q key
	if (e.type == KeyPress && e.xkey.keycode == 53) {
	    XClearWindow(d, w);
	    XNextEvent(d, &e);
	    sleep(2);
	    break;
	}
    }

    XFreeGC(d, gc);
    XCloseDisplay(d);
}

GC create_gc(Display* display, Window win) {
    unsigned long valuemask = 0;
    XGCValues values;
    return XCreateGC(display, win, valuemask, &values);
}

void draw_pixel(Display* d, GC gc, Window w, Colormap screen_colormap,
		char* color, int x, int y) {
    XColor xcolor;
    XAllocNamedColor(d, screen_colormap, color, &xcolor, &xcolor);
    XSetForeground(d, gc, xcolor.pixel);
    XDrawPoint(d, w, gc, x, y);
}
