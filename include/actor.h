#pragma once

#include "object.h"
#include "globals.h"

namespace __game__ {

    class cActor : public cObject {

    public:
        cActor();
        cActor(cActor*);
        ~cActor();

        cActor* parent;

    protected:
        double x, y, z;
        double rotation;
        double scale; //Everything can only be scaled in a nice way because reasons.

        void setRotation(double);
        void setTranslation(double, double, double);
        void setScale(double);

        void translate(double, double, double);
        void rotate(int);
        void scale(double);

        /* Sets the parent nicely without changing the global position */
        void setParent(cActor*);
    };

}
