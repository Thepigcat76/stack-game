#include "utils.h"
#include <stdio.h>
#include <string.h>

Image load_image_asset(char *name) {
  char path[strlen(name) + sizeof("assets/.png")];
  sprintf(path, "assets/%s.png", name);
  Image image = LoadImage(path);
  return image;
}