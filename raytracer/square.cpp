#include "square.h"
#include "vec3.h"


double Square::min_dist_point_to_edge(const point3& point) {
    //int max = MAX_OBJ_DIST;
    double min = 999;
    double dist = 0;
    vec3 v1 = vec3();
    vec3 v2 = vec3();

    for (int i = 0; i < 4; i++) {
        v1 = cross(point - p[i], point - p[(i + 1) % 4]);
        v2 = p[(i + 1) % 4] - p[i];
        dist = v1.length() / v2.length();

        if (dist < min)
            min = dist;
    }
    return min;
}

vec3 Square::reflected_ray(const ray& r) {
    vec3 n = this->normal();
    return r.vec - (2 * (n * dot(r.vec, n)));
}

double Square::ray_to_obj_dist(const ray& r) {
    return -(dot(this->normal(), r.p) + this->d()) / dot(this->normal(), r.vec);
}

bool Square::contains_point(const point3& point) {
    if (this->tri1().contains_point(point) || this->tri2().contains_point(point))
        return true;
    return false;
}

