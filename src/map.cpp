#include "object.h"


/*

a-----b
\  1 /|
 \  / |
  \/ 2|
3 /\  |
 /  \ |
/ 4  \|
c-----d

***TRIGGERED***
*/

namespace __game__ {

    void cMap::render() {
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glTranslated(this->translation.x, this->translation.y, this->translation.z);
        glRotated(this->rotation.x, 1, 0, 0);
        glRotated(this->rotation.y, 0, 1, 0);
        glRotated(this->rotation.z, 0, 0, 1);
        glScaled(this->scale, this->scale, this->scale);

        for (int i = 0; i < this->points.size(); i++) {
            vec3 startPoint = this->points[i++];
            vec3 a = this->points[i++];
            vec3 b = this->points[i++];
            vec3 c = this->points[i++];
            vec3 d = this->points[i];
            vec3 one = (b - startPoint)*(a - startPoint);
            vec3 two = (d - startPoint)*(b - startPoint);
            vec3 three = (a - startPoint)*(c - startPoint);
            vec3 four = (c - startPoint)*(d - startPoint);
            glBegin(GL_TRIANGLES);
            {
                glNormal3d(one.x, one.y, one.z);
                glVertex3d(startPoint.x, startPoint.y, startPoint.z);
                glVertex3d(b.x, b.y, b.z);
                glVertex3d(a.x, a.y, a.z);

                glNormal3d(two.x, two.y, two.z);
                glVertex3d(startPoint.x, startPoint.y, startPoint.z);
                glVertex3d(d.x, d.y, d.z);
                glVertex3d(b.x, b.y, b.z);

                glNormal3d(three.x, three.y, three.z);
                glVertex3d(startPoint.x, startPoint.y, startPoint.z);
                glVertex3d(d.x, d.y, d.z);
                glVertex3d(c.x, c.y, c.z);

                glNormal3d(four.x, four.y, four.z);
                glVertex3d(startPoint.x, startPoint.y, startPoint.z);
                glVertex3d(a.x, a.y, a.z);
                glVertex3d(c.x, c.y, c.z);
            }
            glEnd();
        }
        glPopMatrix();
    }

    void cMap::render(__logger::cLogger* mLog){
        mLog->log("[map.cpp] Information: Rendering map.");
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glTranslated(this->translation.x, this->translation.y, this->translation.z);
        glRotated(this->rotation.x, 1, 0, 0);
        glRotated(this->rotation.y, 0, 1, 0);
        glRotated(this->rotation.z, 0, 0, 1);
        glScaled(this->scale, this->scale, this->scale);

        printf("Drawing %s \n", this->name.c_str());
        for (int i = 0; i < this->points.size(); i++) {
            vec3 startPoint = this->points[i++];
            vec3 a = this->points[i++];
            vec3 b = this->points[i++];
            vec3 c = this->points[i++];
            vec3 d = this->points[i];
            vec3 one = (b - startPoint)*(a - startPoint);
            vec3 two = (d - startPoint)*(b - startPoint);
            vec3 three = (a - startPoint)*(c - startPoint);
            vec3 four = (c - startPoint)*(d - startPoint);
            glBegin(GL_TRIANGLES);
            {
                glNormal3d(one.x, one.y, one.z);
                glVertex3d(startPoint.x, startPoint.y, startPoint.z);
                glVertex3d(b.x, b.y, b.z);
                glVertex3d(a.x, a.y, a.z);
                printf("%.2f %.2f %.2f \n", startPoint.x, startPoint.y, startPoint.z);
                printf("%.2f %.2f %.2f \n", b.x, b.y, b.z);
                printf("%.2f %.2f %.2f \n", a.x, a.y, a.z);

                glNormal3d(two.x, two.y, two.z);
                glVertex3d(startPoint.x, startPoint.y, startPoint.z);
                glVertex3d(d.x, d.y, d.z);
                glVertex3d(b.x, b.y, b.z);
                printf("%.2f %.2f %.2f \n", startPoint.x, startPoint.y, startPoint.z);
                printf("%.2f %.2f %.2f \n", d.x, d.y, d.z);
                printf("%.2f %.2f %.2f \n", b.x, b.y, b.z);

                glNormal3d(three.x, three.y, three.z);
                glVertex3d(startPoint.x, startPoint.y, startPoint.z);
                glVertex3d(d.x, d.y, d.z);
                glVertex3d(c.x, c.y, c.z);
                printf("%.2f %.2f %.2f \n", startPoint.x, startPoint.y, startPoint.z);
                printf("%.2f %.2f %.2f \n", d.x, d.y, d.z);
                printf("%.2f %.2f %.2f \n", c.x, c.y, c.z);

                glNormal3d(four.x, four.y, four.z);
                glVertex3d(startPoint.x, startPoint.y, startPoint.z);
                glVertex3d(a.x, a.y, a.z);
                glVertex3d(c.x, c.y, c.z);
                printf("%.2f %.2f %.2f \n", startPoint.x, startPoint.y, startPoint.z);
                printf("%.2f %.2f %.2f \n", a.x, a.y, a.z);
                printf("%.2f %.2f %.2f \n", c.x, c.y, c.z);
            }
            glEnd();
        }
        glPopMatrix();
    }

}