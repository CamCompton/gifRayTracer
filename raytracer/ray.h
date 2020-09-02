#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray {
public:
    ray() {}
    ray(const point3& origin, const vec3& direction)
        : p(origin), vec(direction)
    {}

    point3 origin() const { return p; }
    vec3 direction() const { return vec; }

    point3 at(double t) const {return p + t * vec;}

public:
    point3 p;
    vec3 vec;
};

#endif