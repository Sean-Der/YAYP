#include "render.h"
#include "y4m.h"

uint8_t *get_frame(Y4M *y4m, int drop_size, int frame_size) {
  uint8_t *buffer;
  buffer = malloc(frame_size);
  fseek(y4m->fp, drop_size, SEEK_CUR);
  fread(buffer, frame_size, 1, y4m->fp);
  return buffer;
}

void yuv_to_rgb(uint8_t y, uint8_t u, uint8_t v, uint8_t *r, uint8_t *g, uint8_t *b) {
  *r = y;
  *g = y;
  *b = y;
}

void renderY4M(Y4M *y4m) {
  XEvent e;
  int s;
  uint8_t r = 0, g = 0, b = 0;
  uint8_t *frame, *moving_frame;
  uint8_t y_color = 0, u_color = 128, v_color = 128;

  Display *d;
  if ((d = XOpenDisplay(NULL)) == NULL) {
    fprintf(stderr, "Cannot open display\n");
    exit(1);
  }

  s = DefaultScreen(d);
  XWindowAttributes atts;
  Window w = XCreateSimpleWindow(d, RootWindow(d, s), 0, 0, y4m->width, y4m->height, 1,
                                 BlackPixel(d, s), WhitePixel(d, s));
  XGetWindowAttributes(d, w, &atts);
  XGCValues values;
  GC gc = XCreateGC(d, w, 0, &values);

  XStoreName(d, w, "y4m player");
  XSelectInput(d, w, ExposureMask | KeyPressMask);
  XMapWindow(d, w);

  char *buff = calloc(1, y4m->width * y4m->height * 4);
  unsigned long offset;
  XImage *xim = XCreateImage(d, NULL, atts.depth, ZPixmap, 0, buff, y4m->width, y4m->height, 8, 0);

  while (1) {

    XNextEvent(d, &e);
    if (e.type == KeyPress && e.xkey.keycode == 53) {
      break;
    }
    if (e.type == KeyPress && e.xkey.keycode == 46) {
      moving_frame = frame = get_frame(y4m, 6, y4m->width * y4m->height * 3);
      offset = 0;

      for (int y = 0; y < y4m->height; y++) {
        for (int x = 0; x < y4m->width; x++) {
          y_color = *(moving_frame++);
          yuv_to_rgb(y_color, u_color, v_color, &r, &g, &b);

          //BGR (May be machine specific)
          buff[offset++] = r | g | b;
          buff[offset++] = r | g | b;
          buff[offset++] = r | g | b;
          offset++;
        }
      }
      XPutImage(d, w, gc, xim, 0, 0, 0, 0, y4m->width, y4m->height);

      free(frame);
      if (feof(y4m->fp)) {
        break;
      }
    }
  }

  XDestroyImage(xim);
  //free(buff);
  XFreeGC(d, gc);
  XCloseDisplay(d);
}
