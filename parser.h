#ifndef PARSER_H
#define PARSER_H

#include <stdlib.h>
#include <string.h>

#include "y4m.h"
#include "error.h"

int readY4M(char *file, Y4M *y4m);
#endif
