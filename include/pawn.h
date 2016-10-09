#pragma once

#include <SDL_opengl.h>
#include <GL/glew.h>
#include <map>
#include <string>

#include "actor.h"

namespace __game__ {

    class cCamera : public cObject {
        /* Attach it to a pawn, just controls the direction I'm looking at */
    public:
        cCamera(cObject*, vec3, double, double); //Cameras are "attached" to pawn in fixed position
        ~cCamera();
        bool isThirdPerson;

        void render() override;

        /* Removing any possibility of me being a retard */
        void translate(vec3) override {}
        void rotate(double) override {}
        void rescale(double) override {} //Why would you ever scale a camera???!?

        void setTranslation(vec3) override {}
        void setRotation(double) override {}
        void setScale(double) override {}
        
        void setThirdPersonDist(double);
    private:
        double thirdPersonDist;

    };

    /* Pawn is a user controllable actor */
    class cPawn : public cActor {
    public:
        cPawn();
        ~cPawn();

        void render() override;

    protected:
        bool renderModel;

        std::map<std::string, cActor> models; //First person/third person
    };

}
