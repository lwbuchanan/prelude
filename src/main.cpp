#include "common.h"

#include "camera.h"
#include "hittable_list.h"
#include "sphere.h"

#include <raylib.h>
#include <string>
#include <unistd.h>

int main(int argc, char *argv[]) {

  // Configure scene
  hittable_list scene;
  scene.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
  scene.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

  // Configure camera
  int width = 400;
  double ratio = 16.0 / 9.0;
  int samples = 100;
  camera camera(width, ratio, samples, 50);

  // Render scene
  camera.render(scene, std::string("image"));

  return 0;
}
