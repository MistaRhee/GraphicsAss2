#include "road.h"

namespace __game__ {

    cRoad::cRoad(double width, double x, double y) {
        this->width = width;
        this->points.push_back(std::make_pair(x, y));
    }

    cRoad::cRoad(double width, std::vector<std::pair<double, double> > inPoints) : cObject(inPoints) {
        this->width = width;
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