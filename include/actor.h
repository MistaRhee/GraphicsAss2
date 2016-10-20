#pragma once

#include "object.h"
#include "globals.h"

namespace __game__ {

    class cActor : public cObject {

    public:
        cActor();
        ~cActor();

        void update();

        void move(double); //Changes increases velocity by ddx
        void setSpeed(vec3); //Sets velocity

    protected:
        vec3 velocity;
    };

}
