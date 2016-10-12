#include "object.h"

namespace __game__ {

    cTree::cTree(double x, double z, double height) {
        this->location = std::make_pair(x, z);
        /* Height is "minimum" height */

        addPoints(height + int(rand() % 4 + 1));
    }

    void cTree::addPoints(double h) {
        /* Trees have radius from 2 units -> 5 units */

    }

}