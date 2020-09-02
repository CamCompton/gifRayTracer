#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"

#include <iostream>
#include <cstdint>
using namespace std;

void write_c(uint8_t* gif_p, color pixel_color) {
 
    gif_p[0] = static_cast<uint8_t>(pixel_color.x());
    gif_p[1] = static_cast<uint8_t>(pixel_color.y());
    gif_p[2] = static_cast<uint8_t>(pixel_color.z());
    gif_p[3] = 0;

}

#endif