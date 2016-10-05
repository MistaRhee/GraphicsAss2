#pragma once

#include <cstdio>
#include <vector>
#include <utility>

#include <SDL.h>
#include <SDL_opengl.h>

#include "globals.h"

namespace __game__ {

    /* To be used as generic components. Actors are the ones with a "render tree" */
    class cObject { //Generic object class
    public:
        cObject();
        ~cObject() {}
        cObject(std::vector<std::pair<double, double> >);
        void render();

        std::pair<double, double> getPoint(int);
        void setPoint(int, double, double);

    protected:
        void setGLFlag(uint32_t); //Sets what type of GL Rendering (lines etc.)

        uint32_t glFlag;
        std::vector<std::pair<double, double> > points;

    };

}
