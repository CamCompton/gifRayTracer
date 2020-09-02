#include "triangle.h"
#include "vec3.h"

double Triangle::min_dist_point_to_edge(const point3& point) {
    double min = 999;
    for (int i = 0; i < 3; i++) {
        double dist = cross(point - p[i], point - p[(i + 1) % 3]).length() / (p[(i + 1) % 3] - p[i]).length();
        if (dist < min)
            min = dist;
    }
    return min;
}

vec3 Triangle::reflected_ray(const ray& r) {
    vec3 n = this->normal();
    return r.vec - (2 * (n * dot(r.vec, n)));
}

double Triangle::ray_to_obj_dist(const ray& r) {
    return -(dot(this->normal(), r.p) + this->d()) / dot(this->normal(), r.vec);
}

bool Triangle::contains_point(const point3& point) {

    point3 v0 = p[2] - p[0];
    point3 v1 = p[1] - p[0];
    point3 v2 = point - p[0];

    double dot00 = dot(v0, v0);
    double dot01 = dot(v0, v1);
    double dot02 = dot(v0, v2);
    double dot11 = dot(v1, v1);
    double dot12 = dot(v1, v2);

    double inv_d = 1 / ((dot00 * dot11) - (dot01 * dot01));
    double u = ((dot11 * dot02) - (dot01 * dot12)) * inv_d;
    double v = ((dot00 * dot12) - (dot01 * dot02)) * inv_d;

    return (u >= 0 - prec) && (v >= 0 - prec) && (u + v < 1 + prec);
}