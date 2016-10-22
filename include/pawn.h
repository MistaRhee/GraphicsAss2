#pragma once

#include <GL/glew.h>
#include <SDL_opengl.h>
#include <map>
#include <string>

#include "actor.h"

namespace __game__ {

    class cCamera : public cActor {
        /* Attach it to a pawn, just controls the direction I'm looking at */
    public:
        cCamera(cObject*, vec3, vec3, double); //Cameras are "attached" to pawn in fixed position
        ~cCamera();

        bool thirdPerson;

        void render() override;
        void render(__logger::cLogger*) override;

        void rotate(double, vec3) override;

        bool collidesWith(cObject*) override { return false; };

        void update(cObject*) override; //Overloaded for free cam
    private:
        const double thirdPersonDist = 2.5; //Camera gets translated 2.5 units backwards

    };

    /* Pawn is a user controllable actor */
    class cPawn: public cActor { //Not really gonna be nice ATM because I"m just hacking stuff up right now.
    public:
        cPawn();
        ~cPawn();

        void setCamera(cCamera*);
        void dropCamera(cObject*); //What to bind the camera to. ROOT if it's not going to hurt anyone....

        void setHeight(double);
        vec3 getPos() { return this->translation; }
        void setThirdPerson(bool);

        void move(vec3) override;

        void printDebug();

    protected:
        cCamera* mCamera;

        const double maxSpeed = 1;
    private:
        void hack();
    };

}
