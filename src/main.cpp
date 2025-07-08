#include "camera.h"
#include "color.h"
#include "hittable.h"
#include "hittable_list.h"
#include "material.h"
#include "quad.h"
#include "rtweekend.h"
#include "vec3.h"
#include <memory>

int main() {
  hittable_list world;

  auto red = make_shared<lambertian>(color(0.65, 0.05, 0.05));
  auto white = make_shared<lambertian>(color(0.73, 0.73, 0.73));
  auto green = make_shared<lambertian>(color(0.12, 0.45, 0.15));
  auto light = make_shared<diffuse_light>(color(15, 15, 15));

  world.add(make_shared<quad>(point3(555, 0, 0), vec3(0, 555, 0),
                              vec3(0, 0, 555), green));
  world.add(make_shared<quad>(point3(0, 0, 0), vec3(0, 555, 0), vec3(0, 0, 555),
                              red));
  world.add(make_shared<quad>(point3(0, 0, 0), vec3(555, 0, 0), vec3(0, 0, 555),
                              white));
  world.add(make_shared<quad>(point3(555, 555, 555), vec3(-555, 0, 0),
                              vec3(0, 0, -555), white));
  world.add(make_shared<quad>(point3(0, 0, 555), vec3(555, 0, 0),
                              vec3(0, 555, 0), white));

  world.add(make_shared<quad>(point3(343, 554, 332), vec3(-130, 0, 0),
                              vec3(0, 0, -105), light));

  shared_ptr<hittable> box1 =
      box(point3(0, 0, 0), point3(165, 330, 165), white);
  box1 = make_shared<rotate_y>(box1, 15);
  box1 = make_shared<translate>(box1, vec3(265, 0, 295));
  world.add(box1);

  shared_ptr<hittable> box2 =
      box(point3(0, 0, 0), point3(165, 165, 165), white);
  box2 = make_shared<rotate_y>(box2, -18);
  box2 = make_shared<translate>(box2, vec3(130, 0, 65));
  world.add(box2);

  camera cam;

  cam.aspect_ratio = 1.0;
  cam.image_width = 600;
  cam.samples_per_pixel = 64;
  cam.max_depth = 50;
  cam.backgroud = color(0, 0, 0);

  cam.vfov = 40;
  cam.lookfrom = point3(278, 278, -800);
  cam.lookat = point3(278, 278, 0);
  cam.vup = point3(0, 1, 0);

  cam.defocus_angle = 0;

  cam.render(world);
}
