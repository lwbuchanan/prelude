#pragma once

#include "hittable.h"

#include <memory>
#include <vector>

using std::make_shared;
using std::shared_ptr;

class hittable_list : public hittable {
public:
  std::vector<shared_ptr<hittable>> hittables;

  hittable_list() {}
  hittable_list(shared_ptr<hittable> hittable) { add(hittable); }

  void add(shared_ptr<hittable> hittable) { hittables.push_back(hittable); }

  bool hit(const ray &ray, double ray_tmin, double ray_tmax,
           hit_record &record) const override {
    hit_record temp_record;
    bool hit_anything = false;
    double current_closest = ray_tmax;

    for (const auto &hittable : hittables) {
      if (hittable->hit(ray, ray_tmin, current_closest, temp_record)) {
        hit_anything = true;
        current_closest = temp_record.t;
        record = temp_record;
      }
    }

    return hit_anything;
  }
};
