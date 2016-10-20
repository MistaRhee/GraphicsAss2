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
        /* Check collisions, adjust accordingly */
    }

    void cActor::move(double a) {
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        this->loadMatrix();
        double mMat[16];
        glGetDoublev(GL_MODELVIEW_MATRIX, mMat);
        vec3 dir(mMat[2 * 4 + 0], mMat[2 * 4 + 1], mMat[2 * 4 + 2]); //What's forwards
        dir.x *= a;
        dir.y *= a;
        dir.z *= a;
        this->velocity += dir;
        glPopMatrix();

        std::string debug;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                debug += std::to_string(mMat[i * 4 + j]) + " ";
            }
            debug += '\n';
        }

        fprintf(stdout, "%s \n", debug.c_str());
    }

    void cActor::setSpeed(vec3 a) {
        this->velocity = a;
    }

}