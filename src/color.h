#pragma once

#include "interval.h"
#include "vec3.h"

using color = vec3;

inline void write_color(std::ostream &out, const color &pixel_color) {
  double r = pixel_color.x();
  double g = pixel_color.y();
  double b = pixel_color.z();

  // [0, 1] -> [0, 255].
  static const interval intensity(0.000, 0.999);
  int rb = int(256 * intensity.clamp(r));
  int gb = int(256 * intensity.clamp(g));
  int bb = int(256 * intensity.clamp(b));

  out << rb << " " << gb << " " << bb << std::endl;
}
