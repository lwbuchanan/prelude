#include "camera.h"

#include "color.h"
#include "common.h"
#include "vec3.h"

#include <fstream>
#include <iostream>

// Public method implementations

void camera::render(const hittable &scene, const std::string &name) {
  std::clog << "Initializing camera...\n";
  initialize();

  // Prepare output image file
  std::ofstream filestream(name + std::string(".ppm"));
  if (!filestream.is_open()) {
    std::cerr << "Failed to open .ppm file\n";
    return;
  }

  // Write PPM header
  filestream << "P3\n" << image_width << " " << image_height << "\n255\n";

  std::clog << "Drawing scene...\n";
  for (int j = 0; j < image_height; j++) {
    std::clog << "\rScanlines left: " << (image_height - j) << ' '
              << std::flush;
    for (int i = 0; i < image_width; i++) {
      // Trace ray from camera into scene
      color pixel_color = color(0, 0, 0);

      for (int sample = 0; sample < samples_per_pixel; sample++) {
        ray ray = get_ray(i, j);
        pixel_color += ray_color(ray, scene);
      }

      // Render the colored pixel
      write_color(filestream, pixel_color * pixel_sample_scale);
    }
  }
  std::clog << "\rDone!               \n";
}

// Private method implementations

void camera::initialize() {

  // Set image dimentions
  image_height = int(image_width / aspect_ratio);
  image_height = (image_height < 1) ? 1 : image_height;

  // Configure the camera
  center = point3(0, 0, 0);
  double focal_length = 1.0;
  pixel_sample_scale = 1.0 / samples_per_pixel;

  // Configure the viewport dimentions
  double viewport_height = 2.0;
  double viewport_width =
      viewport_height * (double(image_width) / image_height);

  // Calculate viewport edge vectors
  vec3 viewport_u = vec3(viewport_width, 0, 0);
  vec3 viewport_v = vec3(0, -viewport_height, 0);

  // Calculate the delta vectors along the edges from pixel to pixel
  pixel_delta_u = viewport_u / image_width;
  pixel_delta_v = viewport_v / image_height;

  // Calculate the location of the origin pixel
  vec3 viewport_upper_left =
      center - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
  origin_pixel = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
}

color camera::ray_color(const ray &ray, const hittable &scene) const {
  hit_record record;
  if (scene.hit(ray, interval(0, infinity), record)) {
    return 0.5 * (record.normal + color(1, 1, 1));
  }

  vec3 ray_direction_unit = unit_vector(ray.direction());
  double a = 0.5 * (ray_direction_unit.y() + 1.0);
  return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}

ray camera::get_ray(int i, int j) const {
  vec3 random_offset = sample_square();
  vec3 pixel_sample = origin_pixel + ((i + random_offset.x()) * pixel_delta_u) +
                      ((j + random_offset.y()) * pixel_delta_v);

  point3 ray_origin = center;
  vec3 ray_direction = pixel_sample - ray_origin;

  return ray(ray_origin, ray_direction);
}

vec3 camera::sample_square() const {
  return vec3(random_double() - 0.5, random_double() - 0.5, 0);
}
