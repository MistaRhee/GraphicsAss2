#include "pawn.h"

namespace __game__ {

    cPawn::cPawn() {
        this->mCamera = NULL;
        hack();
    }

    cPawn::~cPawn() {} //Not gonna destroy camera in here because nature of detachable camera

    void cPawn::setCamera(cCamera* mCam) {
        this->mCamera = mCam;
        this->mCamera->setParent(this);
    }

    void cPawn::dropCamera(cObject* ROOT) {
        this->mCamera->setParent(ROOT);
        this->mCamera = NULL;
    }

    void cPawn::setHeight(double h) {
        this->translation.y = h;
    }

    void cPawn::setThirdPerson(bool t) {
        this->hidden = !t;
        this->mCamera->thirdPerson = t;
    }

    void cPawn::move(vec3 a) {
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        this->mCamera->loadMatrix();
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
        this->velocity += z + x + y;
        glPopMatrix();
        if (this->velocity.x > this->maxSpeed) this->velocity.x = this->maxSpeed;
        if (this->velocity.y > this->maxSpeed) this->velocity.y = this->maxSpeed;
        if (this->velocity.z > this->maxSpeed) this->velocity.z = this->maxSpeed;
    }

    void cPawn::hack() { //Just your average cube, walking about
        this->glFlag = GL_QUADS;

        /* Front */
        addPoint(vec3(0, 0, 0), vec3(0, 0, 1));
        addPoint(vec3(0.1, 0, 0), vec3(0, 0, 1));
        addPoint(vec3(0.1, 0.1, 0), vec3(0, 0, 1));
        addPoint(vec3(0, 0.1, 0), vec3(0, 0, 1));
    	   
        /* Back */
        addPoint(vec3(0, 0, -0.1), vec3(0, 0, -1));
        addPoint(vec3(0, 0.1, -0.1), vec3(0, 0, -1));
        addPoint(vec3(0.1, 0.1, -0.1), vec3(0, 0, -1));
        addPoint(vec3(0.1, 0, -0.1), vec3(0, 0, -1));
    	   
        /* Top */
        addPoint(vec3(0, 0.1, 0), vec3(0, 1, 0));
        addPoint(vec3(0.1, 0.1, 0), vec3(0, 1, 0));
        addPoint(vec3(0.1, 0.1, -0.1), vec3(0, 1, 0));
        addPoint(vec3(0, 0.1, -0.1), vec3(0, 1, 0));

        /* Bottom */
        addPoint(vec3(0, 0, 0), vec3(0, -1, 0));
        addPoint(vec3(0, 0, -0.1), vec3(0, -1, 0));
        addPoint(vec3(0.1, 0, -0.1), vec3(0, -1, 0));
        addPoint(vec3(0.1, 0, 0), vec3(0, -1, 0));

        /* Left */
        addPoint(vec3(0, 0.1, -0.1), vec3(0, -1, 0));
        addPoint(vec3(0, 0, -0.1), vec3(0, -1, 0));
        addPoint(vec3(0, 0, 0), vec3(0, -1, 0));
        addPoint(vec3(0, 0.1, 0), vec3(0, -1, 0));

        /* Right */
        addPoint(vec3(0.1, 0, -0.1), vec3(-1, 0, 0));
        addPoint(vec3(0.1, 0.1, -0.1), vec3(-1, 0, 0));
        addPoint(vec3(0.1, 0.1, 0), vec3(-1, 0, 0));
        addPoint(vec3(0.1, 0, 0), vec3(-1, 0, 0));

        hitBox* hb = new hitBox;
        hb->origin = vec3(0, 0, 0);
        hb->xDir = vec3(0.1, 0, 0);
        hb->yDir = vec3(0, 0.1, 0);
        hb->zDir = vec3(0, 0, -0.1);
        setHitBox(hb);
    }

    void cPawn::printDebug() {
        cObject::printDebug();
        printf("Hidden status: %d \n", this->hidden);
    }

}