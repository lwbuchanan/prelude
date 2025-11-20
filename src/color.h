#pragma once

#include "vec3.h"

using color = vec3;

inline void write_color(std::ostream& out, const color& pixel_color) {
      double r = pixel_color.x();
      double g = pixel_color.y();
      double b = pixel_color.z();

      // [0, 1] -> [0, 255].
      int rb = int(255.99 * r);
      int gb = int(255.99 * g);
      int bb = int(255.99 * b);

      out << rb << " " << gb << " " << bb << std::endl;
}
