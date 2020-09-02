#ifndef TRI_H
#define TRI_H

#include "vec3.h"
#include "shape.h"

class Triangle : public Shape {
public:
    Triangle() {}
    Triangle(const point3& p1, const point3& p2, const point3& p3, const color& col)
        :p{ p1,p2,p3 }, c(col)
    {}
    double prec = .0000001;
    point3 p1() const {}
    point3 p2() const { return p[1]; }
    point3 p3() const { return p[2]; }
    color col() const { return c; }

    vec3 normal() const { return unit_vector(cross(p[1] - p[0], p[2] - p[1])); }
    double d() const { return -dot(p[0], this->normal()); }

    double min_dist_point_to_edge(const point3& point);
    vec3 reflected_ray(const ray& r);
    double ray_to_obj_dist(const ray& r);
    bool contains_point(const point3& point);


public:
    point3 p[3];
    color c;
};




#endif