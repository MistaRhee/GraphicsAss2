#pragma once

#include "mException.h"

/* For the lazy me -_- */
/* Just dump "nice to have" global datastructures here */
struct vec3 {
    vec3() : vec3(0, 0, 0) {}
    vec3(double x, double y, double z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    double x;
    double y;
    double z;
};
