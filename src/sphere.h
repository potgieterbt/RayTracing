#ifndef SPHERE_H
#define SPHERE_H

#include "aabb.h"
#include "hittable.h"
#include "material.h"
#include "rtweekend.h"
#include "vec3.h"
#include <cmath>

class sphere : public hittable {
public:
  // Stationary Sphere
  sphere(const point3 &static_center, double radius, shared_ptr<material> mat)
      : center(static_center, vec3(0, 0, 0)), radius(std::fmax(0, radius)),
        mat(mat) {
    auto rvec = vec3(radius, radius, radius);
    bbox = aabb(static_center - rvec, static_center + rvec);
  }

  // Moving Sphere
  sphere(const point3 &center1, const point3 &center2, double radius,
         shared_ptr<material> mat)
      : center(center1, center2 - center1), radius(std::fmax(0, radius)),
        mat(mat) {
    auto rvec = vec3(radius, radius, radius);
    aabb box1(center.at(0) - rvec, center.at(1) + rvec);
    aabb box2(center.at(1) - rvec, center.at(0) + rvec);
    bbox = aabb(box1, box2);
  }

  bool hit(const ray &r, interval ray_t, hit_record &rec) const override {
    point3 current_center = center.at(r.time());
    vec3 oc = current_center - r.origin();
    auto a = r.direction().length_squared();
    auto h = dot(r.direction(), oc);
    auto c = oc.length_squared() - radius * radius;

    auto discriminant = h * h - a * c;
    if (discriminant < 0) {
      return false;
    }

    auto sqetd = std::sqrt(discriminant);

    auto root = (h - sqetd) / a;
    if (!ray_t.sorrounds(root)) {
      root = (h + sqetd) / a;

      if (!ray_t.sorrounds(root)) {
        return false;
      }
    }
    rec.t = root;
    rec.p = r.at(rec.t);
    vec3 outward_normal = (rec.p - current_center) / radius;
    rec.set_face_normal(r, outward_normal);
    get_sphere_uv(outward_normal, rec.u, rec.v);
    rec.mat = mat;

    return true;
  }

  aabb bounding_box() const override { return bbox; }

private:
  ray center;
  double radius;
  shared_ptr<material> mat;
  aabb bbox;

  static void get_sphere_uv(const point3 &p, double &u, double &v) {
    auto theta = std::acos(-p.y());
    auto phi = atan2(-p.z(), p.x()) + pi;

    u = phi / (2 * pi);
    v = theta / pi;
  }
};

#endif
