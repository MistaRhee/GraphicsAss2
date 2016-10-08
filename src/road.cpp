#include "object.h"

double b(int i, double t) {
    switch (i) {
        case 0:
            return (1 - t) * (1 - t) * (1 - t);
        case 1:
            return 3 * (1 - t) * (1 - t) * t;
        case 2:
            return 3 * (1 - t) * t * t;
        case 3:
            return t * t * t;
        default:
            throw mException(std::string("[road.cpp] Error: Invalid i for Bezier calculation. i = ") + std::to_string(i));
    }
}

namespace __game__ {

    cRoad::cRoad(double width, double x, double y) {
        this->width = width;
        this->points.push_back(std::make_pair(x, y));
        setGLFlag(GL_TRIANGLE_FAN);
    }

    cRoad::cRoad(double width, std::vector<std::pair<double, double> > inPoints) : cObject(inPoints) {
        this->width = width;
        setGLFlag(GL_TRIANGLE_FAN);
        this->prevStart = inPoints[0];
        for (int i = 1; i < inPoints.size();) {
            addSegment(inPoints[i++], inPoints[i++], inPoints[i++]);
        }
    }

    double cRoad::getWidth() {
        return this->width;
    }

    /* Estimate the curve with ~10 points, see how good that looks */
    void cRoad::addSegment(std::pair<double, double> controla, std::pair<double, double> controlb, std::pair<double, double> end) {

        for (int i = 0; i < 10; i++) {
            this->points.push_back(std::make_pair(
                b(0, i/10) * controla.first + b(1, i/10) * controlb.first + b(3, i/10) * end.first,
                b(0, i/10) * controla.second + b(1, i/10) * controlb.second + b(3, i/10) * end.second
                ));
        }
        this->prevStart = end;
    }

}