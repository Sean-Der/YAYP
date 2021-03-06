#ifndef Y4M_H
#define Y4M_H

#include <stdbool.h>
#include <stdio.h>

typedef enum {F30, F25, F24, F30000, F24000} frame_rates;
typedef enum {IP, IT, IB, IM} interlacings;
typedef enum {C420jpeg, C420paldv, C420, C422, C444, Cmono} color_spaces;

struct Y4M {
  FILE *fp;
  int width;
  int height;
  frame_rates frame_rate;
  interlacings interlacing;
  char *aspect_ratio;
  color_spaces color_space;
};

typedef struct Y4M Y4M;
#endif
