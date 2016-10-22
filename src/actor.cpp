#include "actor.h"

/* 
Apparently opengl stores the modelview matrix as
0  4  8  12
1  5  9  13
2  6  10 14
3  7  11 15

Fuck. Everything.
*/

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

    void cActor::move(vec3 a) {
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        this->loadMatrix();
        double mMat[16];
        glGetDoublev(GL_MODELVIEW_MATRIX, mMat);
        vec3 x(mMat[0], mMat[1], mMat[2]);
        vec3 y(mMat[4], mMat[5], mMat[6]);
        vec3 z(mMat[8], mMat[9], mMat[10]); //What's forwards
        x.x *= a.x;
        x.y *= a.x;
        x.z *= a.x;
        y.x *= a.y;
        y.y *= a.y;
        y.z *= a.y;
        z.x *= a.z;
        z.y *= a.z;
        z.z *= a.z;
        this->velocity += z+x+y;
        glPopMatrix();
    }

    void cActor::setSpeed(vec3 a) {
        this->velocity = a;
    }

}