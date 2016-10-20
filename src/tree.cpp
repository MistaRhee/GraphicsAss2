#include "object.h"

namespace __game__ {

    cTree::cTree(double x, double z, double height) {
        /* Height is "minimum" height */
        addPoints(height + int(rand() % 4 + 1));
        this->translation = vec3(x, z, 0);
    }

    void cTree::addPoints(double h) {
        /* Trees have radius from 2 units -> 5 units */
        /* Estimate base with 64 points, Don't need to draw out the base circles, just the cylinders. */
        double angleStep = (2 * M_PI) / 64; //Shamlessly taken from lecture example. Shameless.

        std::vector<vec3> cylinderP;
        std::vector<vec3> cylinderN;
        for (int i = 0; i <= 64; i++) {
            /* Lets keep radius of tree at 1 and radius of the sphere a nice and wonderful 2 */
            double a0 = i * angleStep;
            double a1 = ((i + 1) %  64) * angleStep;

            //Calculate vertices for the quad
            double x0 = cos(a0);
            double y0 = sin(a0);

            double x1 = cos(a1);
            double y1 = sin(a1);
            /* Points go from 0 -> height*/
            /* Render Bottom L -> R, Top R->L */
            cylinderN.push_back(vec3(x0, 0, y0));
            cylinderP.push_back(vec3(x0, 0, y0));

            cylinderN.push_back(vec3(x1, 0, y1));
            cylinderP.push_back(vec3(x1, 0, y1));

            cylinderN.push_back(vec3(x0, 0, y0));
            cylinderP.push_back(vec3(x0, h, y0));

            cylinderN.push_back(vec3(x1, 0, y1));
            cylinderP.push_back(vec3(x1, h, y1));
        }

        this->mCylinder = new cObject(cylinderP, cylinderN);
        this->mCylinder->setName("Tree Trunk");
        this->mCylinder->setParent(this);
        this->mCylinder->setGLFlag(GL_QUAD_STRIP);
        this->mSphere = new cObject(this);
        this->mSphere->translate(vec3(0, 0, h)); //Move the sphere up
        this->mSphere->setName("Tree Leaves");
        this->mSphere->setGLFlag(GL_TRIANGLE_STRIP);
        
        for (int i = 0; i < 10; i++) {
            double theta = 2 * M_PI*i / 10;
            for (int j = 0; j < 10; j++) {
                double phi = 2 * M_PI*j / 10;
                this->mSphere->addPoint(vec3(sin(theta) * cos(phi), sin(theta)*sin(phi), cos(theta)), vec3(sin(theta) * cos(phi), sin(theta)*sin(phi), cos(theta)));
            }
        }

    }

}