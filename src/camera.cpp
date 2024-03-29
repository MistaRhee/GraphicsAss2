﻿#include "pawn.h" //Really shouldn't be in here, but I"m lazy

/* 
Apparently opengl stores the modelview matrix as
0  4  8  12
1  5  9  13
2  6  10 14
3  7  11 15

Fuck. Everything.
*/

namespace __game__ {

    cCamera::cCamera(cObject* p, vec3 t, vec3 r, double s){
        this->parent = p; //if NULL, then camera isn't attached to anything - no collisions
        p->addChild(this);
        this->translation = t;
        this->rotation = r;
        this->scale = s;
        this->thirdPerson = false;
    }

    cCamera::~cCamera() {}

    void cCamera::rotate(double r, vec3 axis) {
        if (axis != vec3(1, 0, 0) && axis != vec3(0, 1, 0) && axis != vec3(0, 0, 1)) abort();
        this->rotation += vec3(axis.x*r, axis.y*r, 0);
        if (this->rotation.x > 90) this->rotation.x = 90;
        if (this->rotation.x < -90) this->rotation.x = -90;
        if (this->rotation.y > 180) this->rotation.y -= 360;
        if (this->rotation.y < -180) this->rotation.y += 360;
    }

    void cCamera::render() {
        glMatrixMode(GL_MODELVIEW);

        loadMatrix();
        double mMatrix[16];
        glGetDoublev(GL_MODELVIEW_MATRIX, mMatrix);
        glScaled(1, 1, -1); //Flips camera properly
        /*
        std::string debug;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                debug += std::to_string(mMatrix[i + j*4]) + " ";
            }
            debug += '\n';
        }

        fprintf(stdout, "%s \n", debug.c_str());
        */

        glLoadIdentity();
        if (thirdPerson) {
            gluLookAt(
                mMatrix[12] + (mMatrix[8] * -this->thirdPersonDist), mMatrix[13] + (mMatrix[9] * -this->thirdPersonDist), mMatrix[14] + (mMatrix[10] * -this->thirdPersonDist),
                mMatrix[12], mMatrix[13], mMatrix[14],
                0, 1, 0
            );
        }
        else {
            gluLookAt(
                mMatrix[12], mMatrix[13], mMatrix[14],
                mMatrix[12] + mMatrix[8], mMatrix[13] + mMatrix[9], mMatrix[14] + mMatrix[10],
                0, 1, 0
            );
        }
    }

    void cCamera::update(cObject* ROOT) {
        this->translate(this->velocity);
    }

    void cCamera::render(__logger::cLogger* mLog) {
        mLog->log("[object.cpp] Info: Rendering object " + this->name);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        loadMatrix();

        double mMatrix[16];
        glGetDoublev(GL_MODELVIEW_MATRIX, mMatrix);

        /*
        std::string debug;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                debug += std::to_string(mMatrix[i + j*4]) + " ";
            }
            debug += '\n';
        }

        fprintf(stdout, "%s \n", debug.c_str());
        */

        gluLookAt(
            mMatrix[12], mMatrix[13], mMatrix[14], 
            mMatrix[8], mMatrix[9], mMatrix[10],
            0, 0, 1 //Shouldn't have rotation around z-axis. Even if it does, I will ignore it. #FuckGeoff
        );
        glPopMatrix();
    }
}

