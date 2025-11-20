#pragma once

#include "ray.h"
#include "vec3.h"

class hit_record {
public:
  point3 point;
  vec3 normal;
  double t;
  bool front_face;

  // Assumes outward_normal is of unit length
  void set_face_normal(const ray& ray, const vec3& outward_normal) {
    front_face = dot(ray.direction(), outward_normal);
    normal = front_face ? outward_normal : -outward_normal;
  }
};

// Interface for objects that rays can interact with
class hittable {
public:
  virtual ~hittable() = default;
  virtual bool hit(const ray &ray, double ray_tmin, double ray_tmax,
                   hit_record &record) const = 0;
};
