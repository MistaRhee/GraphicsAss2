#pragma once

#include <cmath>
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
        cObject(cObject*);
        cObject(vec3, vec3, double);
        cObject(std::vector<vec3>);
        virtual void render();

        vec3 getPoint(int);
        void setPoint(int, vec3);

        cObject* parent;

        void addChild(cObject*);
        void addPoint(vec3);

        /* All rotations are around axis. Be nice. GEOFF THAT MEANS YOU */
        /* Sets the parent nicely without changing the global position */
        void setParent(cObject*);

        virtual void setRotation(vec3);
        virtual void setTranslation(vec3);
        virtual void setScale(double);

        virtual void translate(vec3);
        virtual void rotate(double, vec3);
        virtual void rescale(double);

        bool hidden; //ResidentSleeper

    protected:
        void setGLFlag(uint32_t); //Sets what type of GL Rendering (lines etc.)

        uint32_t glFlag;
        std::vector<vec3> points;

        std::vector<cObject*> children;

        /* Local translation */
        vec3 translation;
        vec3 rotation;
        double scale; //Everything can only be scaled in a nice way because reasons.

    };
    
    /* Assignment specific stuff */

    class cMap : public cObject {
    public:
        void render() override;
    };

    class cRoad : public cObject {
    public:
        cRoad(double, std::vector<std::pair<double, double> >, std::vector<double>, double);
        
        double getWidth();
        void addSegment(std::pair<double, double>, std::pair<double, double>, std::pair<double, double>, std::vector<double>, double); //Starts at A, interpolates B/C

    private:
        double width;
        std::pair<double, double> prevStart;
    };

    class cTree : public cObject {
    public:
        cTree(double, double, double);

        void render() override;
    private:
        void addPoints(double); //Proposed heights, will be built when started

        std::pair<double, double> location;

    };

}
