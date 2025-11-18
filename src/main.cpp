#include "color.h"
#include "vec3.h"

#include <fstream>
#include <iostream>
#include <string>

void draw(std::string filename, int cols, int rows) {
  std::ofstream filestream(filename);

  // Write PPM header
  filestream << "P3\n" << cols << " " << rows << "\n255\n";

  // Write draw some colored vectors
  for (int j = 0; j < rows; j++) {
    std::clog << "\rScanlines left: " << (rows - j) << ' ' << std::flush;
    for (int i = 0; i < cols; i++) {
      color pixel = color(double(i)/(cols-1), double(j)/(rows-1), 0);
      write_color(filestream, pixel);
    }
  }
  std::clog << "\rDone!                     \n";
}

int main(int argc, char *argv[]) {
  std::string filename = "image.ppm";
  draw(filename, 512, 512);
  return 0;
}
