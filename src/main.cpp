#include "common.h"

#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include "color.h"

#include <fstream>
#include <iostream>

color ray_color(const ray &ray, const hittable &world) {
  hit_record record;
  if (world.hit(ray, interval(0, infinity), record)) {
    return 0.5 * (record.normal + color(1, 1, 1));
  }

  vec3 ray_direction_unit = unit_vector(ray.direction());
  double a = 0.5 * (ray_direction_unit.y() + 1.0);
  return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}

void draw_scene(std::string filename, int image_width, int image_height,
                bool raylib) {
  std::clog << "Drawing scene...\n";

  // World
  hittable_list world;
  world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
  world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

  // Define camera
  point3 camera_center = point3(0, 0, 0);
  double focal_length = 1.0;
  double viewport_height = 2.0;
  double viewport_width =
      viewport_height * (double(image_width) / image_height);

  // Edge vectors
  vec3 viewport_u = vec3(viewport_width, 0, 0);
  vec3 viewport_v = vec3(0, -viewport_height, 0);

  vec3 pixel_delta_u = viewport_u / image_width;
  vec3 pixel_delta_v = viewport_v / image_height;

  // Viewport origin position (relative to camera)
  vec3 viewport_upper_left = camera_center - vec3(0, 0, focal_length) -
                             viewport_u / 2 - viewport_v / 2;

  vec3 pixel00_loc =
      viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

  // Prepare output image file
  std::ofstream filestream(filename);
  if (!filestream.is_open()) {
    std::cerr << "Failed to open .ppm file\n";
  }

  // Write PPM header
  filestream << "P3\n" << image_width << " " << image_height << "\n255\n";

  // Render to file
  for (int j = 0; j < image_height; j++) {
    std::clog << "\rScanlines left: " << (image_height - j) << ' '
              << std::flush;
    for (int i = 0; i < image_width; i++) {

      vec3 pixel_center =
          pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
      vec3 ray_direction = pixel_center - camera_center;
      ray ray(camera_center, ray_direction);

      color pixel = ray_color(ray, world);
      write_color(filestream, pixel);
    }
  }
  std::clog << "\rDone!               \n";
}

int main(int argc, char *argv[]) {

  // Define window
  double aspect_ratio = 16.0 / 9.0;
  int window_width = 800;
  int window_height = int(window_width / aspect_ratio);
  window_height = (window_height < 1) ? 1 : window_height;

  std::string filename = "image.ppm";
  draw_scene(filename, window_width, window_height, false);

  return 0;
}
