#ifndef SHAPE_H
#define SHAPE_H

#include "vec3.h"
#include "ray.h"


class Shape {
public:
    virtual double ray_to_obj_dist(const ray& r) = 0;
    virtual bool contains_point(const point3& point) = 0;
    virtual double min_dist_point_to_edge(const point3& point) = 0;
    virtual vec3 reflected_ray(const ray& r) = 0;
    virtual color col() const = 0;


};

#endif