#include "y4m.h"
#include "error.h"
#include "x11.h"
#include "parser.h"

int main(int argc, char *argv[]) {
  Y4M y4m;
  int return_code = 0;

  if (argc != 2) {
    y4m_error("No file specified");
    return_code = 1;
    goto cleanup;
  }

  if (readY4M(argv[1], &y4m)) {
    y4m_error("Failed to parse");
    return_code = 1;
    goto cleanup;
  }

cleanup:
  return return_code;
}

