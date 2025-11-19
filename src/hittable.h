#pragma once

#include "ray.h"

struct hit_record {
  point3 p;
  vec3 normal;
  double t;
};

class hittable {
public:
  virtual ~hittable() = default;
  virtual bool hit(const ray &ray, double ray_tmin, double ray_tmax,
                   hit_record &hit_record) const = 0;
};
