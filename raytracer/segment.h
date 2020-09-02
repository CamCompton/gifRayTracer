#pragma once
#include "ray.h"
class segment :
    public ray
{
public: 
    segment() {}
    segment(const point3& p1, const point3& p2)
        : p{ p1,p2 }, ray(p1, points_to_vector(p1, p2))
    {}
    point3 p1() const { return p[0]; }
    point3 p2() const { return p[1]; }


    

public:
    point3 p[2];
   
};

