#pragma once

#include <map>
#include <string>

#include "actor.h"

namespace __game__ {

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
