#pragma once

#include <vector>
#include <utility>

#include "road.h"

namespace __game__ {

    struct sMap {
        int width;
        int depth;

        double sunlight[3];

        std::vector<std::pair<double, double> > trees;
        std::vector<std::vector<double> > altitudes;

        std::vector<cRoad> mRoads;
    };

}
