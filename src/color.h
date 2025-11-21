#pragma once

#include "common.h"

using color = vec3;
using std::sqrt;

inline double linear_to_gamma2(double linear_component) {
  if (linear_component > 0)
    return sqrt(linear_component);
  return 0;
}

inline void write_color(std::ostream &out, const color &pixel_color) {
  double r = pixel_color.x();
  double g = pixel_color.y();
  double b = pixel_color.z();

  // Apply gamma2 transform
  r = linear_to_gamma2(r);
  g = linear_to_gamma2(g);
  b = linear_to_gamma2(b);

  // [0, 1] -> [0, 255].
  static const interval intensity(0.000, 0.999);
  int rb = int(256 * intensity.clamp(r));
  int gb = int(256 * intensity.clamp(g));
  int bb = int(256 * intensity.clamp(b));

  out << rb << " " << gb << " " << bb << std::endl;
}
