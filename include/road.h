#pragma once

#include <vector>
#include <utility>

#include "object.h"
#include "mException.h"

namespace __game__ {

    class cRoad : public cObject{
    public:
        cRoad(double, double, double);
        cRoad(double, std::vector<std::pair<double, double> >);
        
        double getWidth();
        void addSegment(std::pair<double, double> a, std::pair<double, double> b, std::pair<double, double> c); //Starts at A, interpolates B/C

    private:
        double width;
    };

}