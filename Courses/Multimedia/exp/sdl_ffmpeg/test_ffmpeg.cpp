extern "C" {
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
}
#include <iostream>
int main(int argc, char *argv[]) {
  printf("%s\nOK!", avcodec_configuration());
  return 0;
}