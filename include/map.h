#pragma once

#include <vector>
#include <utility>

#include "road.h"
#include "globals.h"

namespace __game__ {

    struct sMap {
        int width;
        int depth;

        vec3 sunlight;
        vec3 startLoc;

        std::vector<std::pair<double, double> > trees;
        std::vector<double> altitudes;

        std::vector<cRoad> roads;
    };

}
