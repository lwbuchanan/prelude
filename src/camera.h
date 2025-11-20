#pragma once

#include "color.h"
#include "hittable.h"
#include "vec3.h"

/**
 * The camera is a medium between the image and the viewport.
 * The viewport is the virtual screen that exists the "renderworld"
 * and describes the current perspective of the scene. The image
 * is the actual pixels that the viewport will be rendered to and
 * will be visible to the user through an image file or a gui window.
 */
class camera {
public:
  int image_width;
  double aspect_ratio;
  int samples_per_pixel;

  camera(int image_width, double aspect_ratio, int samples_per_pixel)
      : image_width(image_width), aspect_ratio(aspect_ratio),
        samples_per_pixel(samples_per_pixel) {}

  /**
   * Initialize the camera, then draw the scene to `{name}.ppm`
   */
  void render(const hittable &scene, const std::string &name);

private:
  int image_height;
  point3 center;
  point3 origin_pixel;
  vec3 pixel_delta_u;
  vec3 pixel_delta_v;
  double pixel_sample_scale;

  /*
   * Calculate and viewport values based on the camera specification
   */
  void initialize();

  /*
   * Shade the ray based on the hittables it contacts in the scene
   */
  color ray_color(const ray &ray, const hittable &scene) const;

  /*
   * Construct a ray from the camara center to a randomly sampled point around pixel (i,j)
   */
  ray get_ray(int i, int j) const;

  /*
   * Return a random vector in the square [[-0.5,-0.5]] x [[0.5,0.5]]
   */
  vec3 sample_square() const;
};
