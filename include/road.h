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
        void addSegment(std::pair<double, double> start, std::pair<double, double> control, std::pair<double, double> end); //Starts at A, interpolates B/C

    private:
        double width;
        std::pair<double, double> prevStart;
    };

}