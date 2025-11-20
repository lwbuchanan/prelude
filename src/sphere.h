#pragma once

#include "hittable.h"

class sphere : public hittable {
  point3 center;
  double radius;

public:
  sphere(point3 center, double radius)
      : center(center), radius(std::fmax(0, radius)) {}

  bool hit(const ray &ray, interval ray_t,
           hit_record &record) const override {
    vec3 center_offset = center - ray.origin();
    double a = ray.direction().length_squared();
    double h = dot(ray.direction(), center_offset);
    double c = center_offset.length_squared() - radius * radius;

    double discriminant = h * h - a * c;
    if (discriminant < 0) {
      return false;
    }


    double discriminant_sqrt = std::sqrt(discriminant);

    // Get nearest root in range
    double root = (h - discriminant_sqrt) / a;
    if (!ray_t.surrounds(root)) {
      root = (h + discriminant_sqrt) / a;
      if (!ray_t.surrounds(root)) {
        return false;
      }
    }

    record.t = root;
    record.point = ray.at(root);
    vec3 outward_normal = (record.point - center) / radius;
    record.set_face_normal(ray, outward_normal);

    return true;
  }
};
