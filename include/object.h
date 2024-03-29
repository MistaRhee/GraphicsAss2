#pragma once

#include <cmath>
#include <cstdio>
#include <vector>
#include <utility>

#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>

#include "globals.h"
#include "logger.hpp"

namespace __game__ {

    /* To be used as generic components. Actors are the ones with a "render tree" */
    class cObject { //Generic object class
    public:
        cObject();
        ~cObject() {}
        cObject(cObject*);
        cObject(vec3, vec3, double);
        cObject(cObject*, vec3, vec3, double);
        cObject(std::vector<vec3>);
        cObject(std::vector<vec3>, std::vector<vec3>);
        virtual void render();
        virtual void render(__logger::cLogger*);

        vec3 getPoint(int);
        void setPoint(int, vec3);

		cObject* parent;

        void addChild(cObject*);
        void addPoint(vec3);
        void addPoint(vec3, vec3); //Point, normal
        void addPoint(vec3, vec3, vec3); //Point, normal, Texture

        /* All rotations are around axis. Be nice. GEOFF THAT MEANS YOU */
        /* Sets the parent nicely without changing the global position */
        void setParent(cObject*);

        void loadMatrix();

        std::string getName() {
            return this->name;
        }

        void setName(std::string n) {
            this->name = n;
        }

        virtual void setRotation(vec3);
        virtual void setTranslation(vec3);
        virtual void setScale(double);

        virtual void translate(vec3);
        virtual void rotate(double, vec3);
        virtual void rescale(double);

        void setGLFlag(uint32_t); //Sets what type of GL Rendering (lines etc.)

        void printDebug();

        bool hidden = 0; //ResidentSleeper

		void addTex(vec3);

        void setTexID(int);

        void setHitBox(hitBox*);
        void updateHB();

        virtual bool collidesWith(cObject*);

        hitBox* hb;

    protected:

        uint32_t glFlag;
        int texID;
		std::vector<vec3> texture; //Just "texture" things as solid colours ATM
        std::vector<vec3> points;
        std::vector<vec3> normals; //TO ONLY BE USED WITH VERTEX NORMALS (otherwise I will emasculate you, Geoff.

        std::vector<cObject*> children;
		
        /* Local translation */
        vec3 translation;
        vec3 rotation;
        double scale = 1; //Everything can only be scaled in a nice way because reasons.

        std::string name;
    };

    /* Assignment specific stuff */

    class cMap : public cObject {
    public:
        cMap(cObject* parent) : cObject(parent) {}
        void render() override;
        void render(__logger::cLogger*) override;
        bool collidesWith(cObject*) override { return false; }
    };

    class cRoad : public cObject {
    public:
        cRoad(double, std::vector<std::pair<double, double> >, std::vector<double>, double);
        
        double getWidth();
        void addSegment(std::pair<double, double>, std::pair<double, double>, std::pair<double, double>, std::vector<double>, double); //Starts at A, interpolates B/C
		void render() override;

    private:
        double width;
        std::pair<double, double> prevStart;
    };

    class cTree : public cObject {
    public:
        cTree(double, double, double, GLuint);

    private:
        void addPoints(double); //Proposed heights, will be built when started

        /* Actually just gonna neck myself for being so gosh darned stupid -_- */
        cObject* mCylinder;
        cObject* mLeaves;
        
    };

    class cPortal : public cObject {
    public:
        cPortal(std::pair<vec3, vec3>, double, std::vector<double>, double); //Location, height

        bool collidesWith(cObject*) override;
        void addPartner(cPortal*);

        void teleport(cObject*);
        void setHeight(std::vector<double>, double);

        bool passes(vec3);

        vec3 perp;

    private:
        std::pair<vec3, vec3> location;
        cPortal* partner; //Where this portal leads to

        double height;
    };

    class cBush : public cObject {
    public:
        cBush(double, double);

        void setHeight(double h);

        void render() override;

    private:
        int vertShader;
        int fragShader;
        int shaderProgram;
    };

}
