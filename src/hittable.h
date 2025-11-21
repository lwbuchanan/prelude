#pragma once

#include "common.h"

class material;

class hit_record {
public:
  point3 point;
  vec3 normal;
  shared_ptr<material> material;
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
  virtual bool hit(const ray &ray, interval ray_t,
                   hit_record &record) const = 0;
};
