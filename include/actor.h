#pragma once

#include "object.h"

namespace __game__ {

    class cActor : public cObject {

    public:
        cActor();
        ~cActor();

    protected:
        double x, y, z;
        int rotation;
        double scale; //Everything can only be scaled in a nice way because reasons.

        void setRotation(int);
        void setTranslation(double, double, double);
        void setScale(double);

        void translate(double, double, double);
        void rotate(int);
        void scale(double);
    };

}
