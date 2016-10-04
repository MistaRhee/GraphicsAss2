#include "road.h"

namespace __game__ {

    cRoad::cRoad(double width, double x, double y) {
        this->width = width;
        this->points.push_back(std::make_pair(x, y));
        setGLFlag(GL_TRIANGLE_FAN);
    }

    cRoad::cRoad(double width, std::vector<std::pair<double, double> > inPoints) : cObject(inPoints) {
        this->width = width;
        setGLFlag(GL_TRIANGLE_FAN);
    }

    double cRoad::getWidth() {
        return this->width;
    }

    /* Estimate the curve with ~30 points, see how good that looks */
    void cRoad::addSegment(std::pair<double, double> start, std::pair<double, double> control, std::pair<double, double> end) {

    }

    /*
    double cRoad::bezierCoeff(int i, double t) {
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
    */

}