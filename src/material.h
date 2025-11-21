#pragma once

#include "color.h"
#include "hittable.h"

class material {
public:
  virtual ~material() = default;

  virtual bool scatter(const ray &ray_in, const hit_record &record,
                       color &attenuation, ray &ray_scattered) const {
    return false;
  }
};
