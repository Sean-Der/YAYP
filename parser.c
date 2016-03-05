#include "parser.h"

int width_read(char *val, Y4M *y4m) {
  y4m->width = strtol(val, NULL, 10);
  return 0;
}
int height_read(char *val, Y4M *y4m) {
  y4m->height = strtol(val, NULL, 10);
  return 0;
}
int frame_rate_read(char *val, Y4M *y4m) {
  if (!strcmp("30:1", val)) {
    y4m->frame_rate = F30;
  } else if (!strcmp("25:1", val)) {
    y4m->frame_rate = F25;
  } else if (!strcmp("24:1", val)) {
    y4m->frame_rate = F24;
  } else if (!strcmp("30000:1001", val)) {
    y4m->frame_rate = F30000;
  } else if (!strcmp("24000:1001", val)) {
    y4m->frame_rate = F24000;
  } else {
    y4m_error("Invalid or missing frame rate: %s", val);
    return 1;
  }

  return 0;
}
int interlacing_read(char *val, Y4M *y4m) {
  if (!strcmp("p", val)) {
    y4m->interlacing = IP;
  } else if (!strcmp("t", val)) {
    y4m->interlacing = IT;
  } else if (!strcmp("b", val)) {
    y4m->interlacing = IB;
  } else if (!strcmp("m", val)) {
    y4m->interlacing = IM;
  } else {
    y4m_error("Invalid or missing interlacing: %s", val);
    return 1;
  }

  return 0;
}
int aspect_ratio_read(char *val, Y4M *y4m) {
  if (!strcmp("A0:0", val)) {
    y4m->aspect_ratio = A00;
  } else if (!strcmp("A1:1", val)) {
    y4m->aspect_ratio = A11;
  } else if (!strcmp("A4:3", val)) {
    y4m->aspect_ratio = A43;
  } else if (!strcmp("A4:5", val)) {
    y4m->aspect_ratio = A45;
  } else if (!strcmp("A32:27", val)) {
    y4m->aspect_ratio = A3227;
  } else {
    y4m_error("Invalid aspect ratio: %s", val);
    return 1;
  }

  return 0;
}
int color_space_read(char *val, Y4M *y4m) {
  if (!strcmp("C420jpeg", val)) {
    y4m->color_space = C420jpeg;
  } else if (!strcmp("C420paldv", val)) {
    y4m->color_space = C420paldv;
  } else if (!strcmp("C420", val)) {
    y4m->color_space = C420;
  } else if (!strcmp("C422", val)) {
    y4m->color_space = C422;
  } else if (!strcmp("C444", val)) {
    y4m->color_space = C444;
  } else {
    y4m_error("Invalid color space: %s", val);
    return 1;
  }

  return 0;
}

int header_parser(char *buff, Y4M *y4m, char arg, int (*cb) (char *val, Y4M *y4m)) {
  char *start = NULL, *end;

  for (end = buff; (*end - 1) != '\0'; end++) {
    if (start == NULL && *end == arg) {
      start = end + 1;
    } else if (start && (*end == ' ' || *end == '\0')) {
      char new[end - start + 1];
      strncpy(new, start, end - start);
      new[end - start] = '\0';
      return cb(new, y4m);
    }
  }
  return 1;
}

int readY4M(char *file, Y4M *y4m) {
  //TODO handle header > 1028
  char buff[1028];
  int return_code = 0;


  if ((y4m->fp = fopen(file, "r")) == NULL) {
    y4m_error("%s does not exist", file);
    return 1;
  }
  fgets(buff, sizeof(buff), y4m->fp);
  if (strstr(buff, "YUV4MPEG2") == NULL) {
    y4m_error("No Header");
    return 1;
  }

  if (header_parser(buff, y4m, 'C', color_space_read)) {
    y4m_error("Missing color_space, defaulting to C420");
    y4m->color_space = C420;
  }

  if (header_parser(buff, y4m, 'W', width_read)) {
    y4m_error("Missing width");
    return_code = 1;
  }

  if (header_parser(buff, y4m, 'H', height_read)) {
    y4m_error("Missing height");
  }

  if (header_parser(buff, y4m, 'F', frame_rate_read)) {
    y4m_error("Missing frame rate");
    return_code = 1;
  }

  if (header_parser(buff, y4m, 'I', width_read)) {
    y4m_error("Missing interlacing");
    return_code = 1;
  }

  if (header_parser(buff, y4m, 'A', width_read)) {
    y4m_error("Missing aspect ratio");
    return_code = 1;
  }

  return return_code;
}
