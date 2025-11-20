#pragma once

#include "common.h"

class interval {
public:
  double min, max;

  interval() : min(-infinity), max(infinity) {}

  interval(double min, double max) : min(min), max(max) {}

  double size() const { return max - min; }

  // Exclusive bounds
  bool contains(double value) { return min < value && value < max; }

  // Inclusive bounds
  bool surrounds(double value) { return min <= value && value <= max; }

  static const interval empty, universe;
};


inline const interval interval::empty = interval(infinity, -infinity);
inline const interval interval::universe = interval(-infinity, infinity);
