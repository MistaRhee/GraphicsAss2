#include "object.h"

namespace __game__ {
    
    cPortal::cPortal(std::pair<vec3, vec3> loc, double height) {
        this->height = height;
        this->location = loc;
    }

    bool cPortal::collidesWith(cObject* obj) {
        if(obj->hb)
    }

}