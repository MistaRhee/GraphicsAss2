#pragma once

#include "object.h"
#include "globals.h"

namespace __game__ {

    class cActor : public cObject {

    public:
        cActor();
        ~cActor();

        virtual void update(cObject*);

        virtual void move(vec3); //Changes increases velocity by ddx
        void setSpeed(vec3); //Sets velocity

    protected:
        vec3 velocity;
    };

}
