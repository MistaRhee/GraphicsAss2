#include "pawn.h" //Really shouldn't be in here, but I"m lazy


namespace __game__ {

    cCamera::cCamera(cObject* p, vec3 t, double r, double s) : cObject(t, r, s) {
        this->parent = p; //if NULL, then camera isn't attached to anything - no collisions
    }

    cCamera::~cCamera() {}

    void cCamera::render() {
        /* Shouldn't have rotation around z */
        gluLookAt(
            this->translation.x, this->translation.y, this->translation.z,
            
            0, 0, 1);
    }

    void cCamera::setThirdPersonDist(double dist) {
        this->thirdPersonDist = dist;
    }
}

