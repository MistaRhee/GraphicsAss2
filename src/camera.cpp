#include "pawn.h" //Really shouldn't be in here, but I"m lazy


namespace __game__ {

    cCamera::cCamera(cObject* p, vec3 t, double r, double s) : cObject(t, r, s) {
        this->parent = p; //if NULL, then camera isn't attached to anything
    }

    cCamera::~cCamera() {}

    void cCamera::render() {
    }
}

