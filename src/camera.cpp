#include "pawn.h" //Really shouldn't be in here, but I"m lazy


namespace __game__ {

    cCamera::cCamera(cObject* p, vec3 t, vec3 r, double s) : cObject(t, r, s) {
        this->parent = p; //if NULL, then camera isn't attached to anything - no collisions
    }

    cCamera::~cCamera() {}

    void cCamera::render() {
        glPushMatrix();
        glTranslated(this->translation.x, this->translation.y, this->translation.z);
        glRotated(this->rotation.x, 1, 0, 0);
        glRotated(this->rotation.y, 0, 1, 0);
        glRotated(this->rotation.z, 0, 0, 1);
        glScaled(this->scale, this->scale, this->scale);

        double* mMatrix = NULL;
        glGetDoublev(GL_MODELVIEW_MATRIX, mMatrix);

        gluLookAt(
            mMatrix[0 * 4 + 3], mMatrix[1 * 4 + 3], mMatrix[2 * 4 + 3], //Formatting for easier "2d"-iness ¯\_(ツ)_/¯
            mMatrix[2 * 4 + 0], mMatrix[2 * 4 + 1], mMatrix[2 * 4 + 2], 
            0, 0, 1 //Shouldn't have rotation around z-axis. Even if it does, I will ignore it. #FuckGeoff
            );
        glPopMatrix();
    }

    void cCamera::setThirdPersonDist(double dist) {
        this->thirdPersonDist = dist;
    }
}

