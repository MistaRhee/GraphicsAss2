#include "object.h"

namespace __game__ {

    cTree::cTree(double x, double z) {
        this->location = std::make_pair(x, z);
        this->pointsGenerated = false;
    }

    void cTree::addHeights(double h) {
        //TODO: Finish this
    }

}