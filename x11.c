#include "x11.h"
#include "y4m.h"

void drawPixelMap(void) {
  Display *d;
  XEvent e;
  int s;
  if ((d = XOpenDisplay(NULL)) == NULL) {
    fprintf(stderr, "Cannot open display\n");
    exit(1);
  }

  s = DefaultScreen(d);
  Window w = XCreateSimpleWindow(d, RootWindow(d, s), 0, 0, 500, 500, 1,
                                 BlackPixel(d, s), WhitePixel(d, s));
  GC gc = create_gc(d, w);
  Colormap screen_colormap = DefaultColormap(d, s);

  // Pixmap pixmap = XCreatePixmap(
  //    d, w, 500, 500, DefaultDepthOfScreen(DefaultScreenOfDisplay(d)));
  // XCopyArea(d, pixmap, w, gc, 0, 0, 300, 300, 0, 0);

  XStoreName(d, w, "y4m player");
  XSelectInput(d, w, ExposureMask | KeyPressMask);
  XMapWindow(d, w);

  for (int x = 0; x <= 300; x++) {
    for (int y = 0; y <= 300; y++) {
      draw_pixel(d, gc, w, screen_colormap, (y % 2) ? "red" : "green", x, y);
    }
  }

  while (1) {
    XNextEvent(d, &e);
    // q key
    if (e.type == KeyPress && e.xkey.keycode == 53) {
      break;
    }
  }

  XFreeGC(d, gc);
  XCloseDisplay(d);
}

GC create_gc(Display *display, Window win) {
  unsigned long valuemask = 0;
  XGCValues values;
  return XCreateGC(display, win, valuemask, &values);
}

void draw_pixel(Display *d, GC gc, Window w, Colormap screen_colormap,
                char *color, int x, int y) {
  XColor xcolor;
  XAllocNamedColor(d, screen_colormap, color, &xcolor, &xcolor);
  XSetForeground(d, gc, xcolor.pixel);
  XDrawPoint(d, w, gc, x, y);
}
