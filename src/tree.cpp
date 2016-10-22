#include "object.h"

namespace __game__ {

    cTree::cTree(double x, double z, double height, GLuint pap) {
        /* Height is "minimum" height */
        addPoints(height + ((double)(rand() % 2)) + 1);
        this->translation = vec3(x, 0, z);
        this->texID = pap;
    }

    void cTree::addPoints(double h) {
        /* Trees have radius from 2 units -> 5 units */
        /* Estimate base with 64 points, Don't need to draw out the base circles, just the cylinders. */
        double angleStep = (2 * M_PI) / 64; //Shamlessly taken from lecture example. Shameless.

        std::vector<vec3> cylinderP;
        std::vector<vec3> cylinderN;
        this->mCylinder = new cObject(cylinderP, cylinderN);
        this->mCylinder->setName("Tree Trunk");
        this->mCylinder->setParent(this);
        this->mCylinder->setGLFlag(GL_QUAD_STRIP);
        this->mCylinder->setTexID(this->texID);
        for (int i = 0; i <= 64; i++) {
            /* Lets keep radius of tree at 1 and radius of the sphere a nice and wonderful 2 */
            double a0 = i * angleStep;
            double a1 = ((i + 1) % 64) * angleStep;

            //Calculate vertices for the quad
            double x0 = cos(a0) * 0.1;
            double y0 = sin(a0) * 0.1;

            double x1 = cos(a1) * 0.1;
            double y1 = sin(a1) * 0.1;
            /* Points go from 0 -> height*/
            /* Render Bottom L -> R, Top R->L */
            
            this->mCylinder->addPoint(vec3(x0, 0, y0), vec3(x0, 0, y0), vec3(0.25, 1, 0));
            this->mCylinder->addPoint(vec3(x1, 0, y1), vec3(x1, 0, y1), vec3(0.5, 1, 0));
            this->mCylinder->addPoint(vec3(x0, h, y0), vec3(x0, 0, y0), vec3(0.25, 0, 0));
            this->mCylinder->addPoint(vec3(x1, h, y1), vec3(x1, 0, y1), vec3(0.5, 0, 0));
        }
        hitBox* chb = new hitBox;
        chb->origin = vec3(0.1, 0, 0.1);
        chb->xDir = vec3(0.2, 0, 0);
        chb->yDir = vec3(0, h, 0);
        chb->zDir = vec3(0, 0, 0.2);
        this->mCylinder->setHitBox(chb);

        this->mLeaves = new cObject(this);
        this->mLeaves->translate(vec3(0, h, 0)); //Move the sphere up
        this->mLeaves->setName("Tree Leaves");
        this->mLeaves->setGLFlag(GL_TRIANGLE_FAN);
        this->mLeaves->setTexID(this->texID); //No hitbox for leaves

        for (int i = 0; i < 10; i++) {
            double phi = 2 * M_PI*i / 10;
            for (int j = 0; j < 10; j++) {
                double theta = 2 * M_PI*j / 10;
                this->mLeaves->addPoint(vec3(sin(theta) * cos(phi) * 0.4, cos(theta)*0.4, sin(theta)*sin(phi) * 0.4), vec3(sin(theta) * cos(phi) * 0.4, cos(theta)*0.4, sin(theta)*sin(phi)*0.4), vec3(0.6, 0.6, 0));
            }
        }

    }

}