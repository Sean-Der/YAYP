#include "y4m.h"
#include "error.h"
#include "render.h"
#include "parse.h"

int main(int argc, char *argv[]) {
  Y4M y4m = {.aspect_ratio = NULL};
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
  renderY4M(&y4m);

cleanup:
  if (y4m.aspect_ratio) {
    free(y4m.aspect_ratio);
  }

  return return_code;
}
