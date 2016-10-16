#include "object.h"

namespace __game__ {

    cTree::cTree(double x, double z, double height) {
        this->location = std::make_pair(x, z);
        /* Height is "minimum" height */

        addPoints(height + int(rand() % 4 + 1));
    }

    void cTree::addPoints(double h) {
        /* Trees have radius from 2 units -> 5 units */
        double radius = (int)rand()%3+2;
        /* Estimate base with 64 points, Don't need to draw out the base circles, just the cylinders. */
        for (int i = 0; i < 64; i++) {
            double theta = (2 * M_PI) * i / 64;
            /* Points go from 0 -> height*/
            /* Render Bottom L -> R, Top R->L */
        }
    }

    void cTree::render() {
        glBegin(GL_QUAD_STRIP);
        {
            for (int i = 0; i < 128; i++) {

            }
        }
        glEnd();
        glBegin(GL_TRIANGLE_STRIP);
        {

        }
        glEnd();
    }

}