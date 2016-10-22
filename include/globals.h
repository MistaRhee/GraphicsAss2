#pragma once

#include "mException.h"

/* For the lazy me -_- */
/* Just dump "nice to have" global datastructures here */
struct vec3 {
    vec3() : vec3(0, 0, 0) {}
    vec3(double) : vec3(0, 0, 0) {}
    vec3(double x, double y, double z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    vec3& operator+=(const vec3& rhs) {
        this->x += rhs.x;
        this->y += rhs.y;
        this->z += rhs.z;
        return *this;
    }

    vec3& operator-=(const vec3& rhs) {
        this->x -= rhs.x;
        this->y -= rhs.y;
        this->z -= rhs.z;
        return *this;
    }

    vec3& operator*=(const vec3& rhs) { //Cross product
        return vec3(this->y*rhs.z - this->z*rhs.y, this->z*rhs.x - this->x*rhs.z, this->x*rhs.y - this->y*rhs.x);
    }

    friend vec3 operator*(vec3 lhs, const vec3& rhs) {
        return lhs *= rhs;
    }

    friend vec3 operator+(vec3 lhs, const vec3& rhs) {
        return lhs += rhs;
    }

    friend vec3 operator-(vec3 lhs, const vec3& rhs) {
        return lhs -= rhs;
    }

    friend bool operator==(const vec3& lhs, const vec3& rhs) {
        return((lhs.x == rhs.x) && (lhs.y == rhs.y) && (lhs.z == rhs.z));
    }

    friend bool operator!=(const vec3& lhs, const vec3& rhs) {
        return(!(lhs == rhs));
    }

    double dot(vec3 rhs) {
        return (this->x*rhs.x + this->y*rhs.y + this->z*rhs.z);
    }

    double x;
    double y;
    double z;
};

struct hitBox {
    vec3 xDir, yDir, zDir;
    vec3 originDisp; //smallest x, y, z corner
    vec3 origin;

    bool intersects(hitBox other) {
        if (origin.x > (other.origin + other.xDir).x) return false;
        if (other.origin.x < (origin + xDir).x) return false;
        if (origin.y > (other.origin + other.yDir).y) return false;
        if (other.origin.y < (origin + yDir).y) return false;
        if (origin.z > (other.origin + other.zDir).z) return false;
        if (other.origin.z < (origin + zDir).z) return false;

        return true;
    }
};

