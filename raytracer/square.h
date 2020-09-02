#ifndef SQR_H
#define SQR_H

#include "vec3.h"
#include "ray.h"
#include "triangle.h"


class Square : public Shape {
public:
    Square() {}
    Square(const point3& p1, const point3& p2, const point3& p3, const point3& p4, const color& col)
        :p{ p1,p2,p3,p4 }, c(col)
    {}

    point3 p1() const { return p[0]; }
    point3 p2() const { return p[1]; }
    point3 p3() const { return p[2]; }
    point3 p4() const { return p[3]; }
    color col() const { return c; }

    vec3 normal() const { return unit_vector(cross(p[1] - p[0], p[2] - p[1])); }
    double d() const { return -dot(p[0], this->normal()); }

    double min_dist_point_to_edge(const point3& point);
    vec3 reflected_ray(const ray& r);
    bool contains_point(const point3& point);
    double ray_to_obj_dist(const ray& r);

    Triangle tri1() const { return Triangle(p[0], p[1], p[2], color()); }
    Triangle tri2() const { return Triangle(p[2], p[3], p[0], color()); }


public:
    point3 p[4];
    color c;

};








#endif