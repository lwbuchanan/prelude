#include "color.h"
#include "ray.h"
#include "vec3.h"

#include <cmath>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <unistd.h>

namespace rl {
extern "C" {
#include <raylib.h>
}
} // namespace rl

double hit_sphere(const point3 &center, double radius, const ray &ray) {
  vec3 center_offset = center - ray.origin();
  double a = ray.direction().length_squared(); 
  double h = dot(ray.direction(), center_offset);
  double c = center_offset.length_squared() - radius * radius;
  double discriminant = h * h - a * c;
  if (discriminant < 0) {
    return -1.0;
  }
  return (h - std::sqrt(discriminant)) / a;
}

color ray_color(const ray &ray) {
  // Get the hit point of the sphere, if there is one
  double point = hit_sphere(point3(0, 0, -1), 0.5, ray);
  if (point > 0) {
    vec3 normal = unit_vector(ray.at(point) - point3(0, 0, -1));
    return 0.5 * color(1 + normal.x(), 1 + normal.y(), 1 + normal.z());
  }

  vec3 ray_direction_unit = unit_vector(ray.direction());
  double a = 0.5 * (ray_direction_unit.y() + 1.0);
  return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}

rl::Color to_rl_color(const color &c) {
  return rl::ColorFromNormalized(
      {float(c.x()), float(c.y()), float(c.z()), 1.0});
}

void draw_scene(std::string filename, int image_width, int image_height,
                bool raylib) {
  std::clog << "Drawing scene...\n";

  // Define camera
  double focal_length = 1.0;
  double viewport_height = 2.0;
  double viewport_width =
      viewport_height * (double(image_width) / image_height);
  point3 camera_center = point3(0, 0, 0);

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

  // Write draw some colored vectors
  for (int j = 0; j < image_height; j++) {
    std::clog << "\rScanlines left: " << (image_height - j) << ' '
              << std::flush;
    for (int i = 0; i < image_width; i++) {

      vec3 pixel_center =
          pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
      vec3 ray_direction = pixel_center - camera_center;
      ray r(camera_center, ray_direction);

      color pixel = ray_color(r);
      write_color(filestream, pixel);
      if (raylib) {
        if (i == 0 && j % 5 == 0) {
          rl::EndDrawing();
          rl::BeginDrawing();
        }
        rl::DrawPixel(i, j, to_rl_color(pixel));
      }
    }
  }
  std::clog << "\rDone!                     \n";
}

int main(int argc, char *argv[]) {
  double aspect_ratio = 16.0 / 9.0;
  int window_width = 800;
  int window_height = int(window_width / aspect_ratio);
  window_height = (window_height < 1) ? 1 : window_height;
  std::string filename = "image.ppm";

  bool raylib = false;
  if (raylib) {
    rl::InitWindow(window_width, window_height, "Prelude");
    rl::BeginDrawing();
    draw_scene(filename, window_width, window_height, true);
    rl::EndDrawing();

    while (!rl::WindowShouldClose()) {
      rl::BeginDrawing();
      sleep(1);
      rl::EndDrawing();
    }
    rl::CloseWindow();
  } else {
    draw_scene(filename, window_width, window_height, false);
  }

  return 0;
}
