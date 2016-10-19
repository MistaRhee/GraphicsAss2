#include "actor.h"

namespace __game__ {

    cActor::cActor() {
        this->translation = vec3(0, 0, 0);
        this->rotation = vec3(0, 0, 0);
        this->scale = 1;
        this->parent = NULL;
    }

    cActor::~cActor() {}

    void cActor::update() {
        this->translate(this->velocity);
    }

    void cActor::move(vec3 a) {
        this->velocity += a;
    }

    void cActor::setSpeed(vec3 a) {
        this->velocity = a;
    }

}