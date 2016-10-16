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
        /* Estimate base with 64 points */
        for (int i = 0; i < 64; i++) {
            double theta = (2 * M_PI) * i / 64;
            /* Points go from 0 -> height*/
        }
    }

    void cTree::render() {

    }

}