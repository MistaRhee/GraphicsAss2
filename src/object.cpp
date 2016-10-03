#include "object.h"

namespace __game__ {

    cObject::cObject(std::vector<std::pair<double, double> > points) {
        this->points = std::vector<std::pair<double, double> >(points);
        this->glFlag = GL_TRIANGLE_FAN;
    }

    void cObject::render() {
        glBegin(glFlag);
        {
            for (auto p : this->points) {
                glVertex2d(p.first, p.second);
            }
        }
        glEnd();
    }
}