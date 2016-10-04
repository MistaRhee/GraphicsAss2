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

    std::pair<double, double> cObject::getPoint(int index) {
        return this->points[index];
    }

    void cObject::setPoint(int index, double x, double y) {
        this->points[index] = std::make_pair(x, y);
    }

    void cObject::setGLFlag(uint32_t flag) {
        this->glFlag = flag;
    }
}