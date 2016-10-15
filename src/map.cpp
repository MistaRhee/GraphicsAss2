#include "object.h"

namespace __game__ {

    void cMap::render() {
        for (int i = 0; i < this->points.size(); i++) {
            glBegin(GL_TRIANGLE_FAN);
            {
                glVertex3d(this->points[i].x, this->points[i].y, this->points[i++].z);
                glVertex3d(this->points[i].x, this->points[i].y, this->points[i++].z);
                glVertex3d(this->points[i].x, this->points[i].y, this->points[i++].z);
                glVertex3d(this->points[i].x, this->points[i].y, this->points[i++].z);
                glVertex3d(this->points[i].x, this->points[i].y, this->points[i++].z);
            }
            glEnd();
        }
    }

}