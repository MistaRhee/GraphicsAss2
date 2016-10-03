#pragma once

#include <cstdio>
#include <vector>
#include <utility>

#include <SDL.h>
#include <SDL_opengl.h>

#include "mException.h"


namespace __game__ {

    class cObject { //Generic object class
    public:
        cObject(std::vector<std::pair<double, double> >);
        void render();

        std::pair<double, double> getPoint(int);
        void setPoint(int, double, double);

        void setGLFlag(uint32_t); //Sets what type of GL Rendering (lines etc.)

    protected:
        uint32_t glFlag;
        std::vector<std::pair<double, double> > points;

    };

}
