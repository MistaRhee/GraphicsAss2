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
        bool isThirdPerson;

        void render() override;
        void render(__logger::cLogger*) override;

        void rotate(double, vec3) override;

        void setThirdPersonDist(double);
    private:
        double thirdPersonDist;

    };

    /* Pawn is a user controllable actor */
    class cPawn : public cActor {
    public:
        cPawn();
        ~cPawn();

    protected:

        cCamera* mCamera;

        std::map<std::string, cActor> models; //First person/third person
    };

}
