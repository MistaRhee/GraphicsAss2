#include "object.h"

namespace __game__ {

    cObject::cObject() {
        this->glFlag = GL_TRIANGLE_FAN;
        this->hidden = false;
        this->translation = vec3(0, 0, 0);
        this->rotation = vec3(0, 0, 0);
        this->scale = 1;
        this->parent = NULL;
    }

    cObject::cObject(cObject* parent) : cObject() {
        this->parent = parent;
        parent->addChild(this);
    }

    cObject::cObject(vec3 t, vec3 r, double s) : cObject() {
        this->translation = t;
        this->rotation = r;
        this->scale = s;
    }

    cObject::cObject(cObject* parent, vec3 t, vec3 r, double s) : cObject(parent) {
        this->translation = t;
        this->rotation = r;
        this->scale = s;
    }

    cObject::cObject(std::vector<vec3> points) : cObject() {
        this->points = std::vector<vec3>(points);
    }

    cObject::cObject(std::vector<vec3> points, std::vector<vec3> normals) : cObject() {
        this->points = std::vector<vec3>(points);
    }

    void cObject::loadMatrix() {
        glMatrixMode(GL_MODELVIEW);
        if (this->parent == NULL) {
            glLoadIdentity();
        }
        else {
            this->parent->loadMatrix();
        }
        glTranslated(this->translation.x, this->translation.y, this->translation.z);
        glRotated(this->rotation.x, 1, 0, 0);
        glRotated(this->rotation.y, 0, 1, 0);
        glRotated(this->rotation.z, 0, 0, 1);
        glScaled(this->scale, this->scale, this->scale);
    }

    void cObject::render(__logger::cLogger* mLog) {
        mLog->log("[object.cpp] Info: Rendering object " + this->name);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glTranslated(this->translation.x, this->translation.y, this->translation.z);
        glRotated(this->rotation.x, 1, 0, 0);
        glRotated(this->rotation.y, 0, 1, 0);
        glRotated(this->rotation.z, 0, 0, 1);
        glScaled(this->scale, this->scale, this->scale);
        if (!hidden) {
            glBegin(glFlag);
            {
                if (this->normals.size() == this->points.size()) {
                    for (int i = 0; i < this->points.size(); i++) {
                        glNormal3d(this->normals[i].x, this->normals[i].y, this->normals[i].z);
                        glVertex3d(this->points[i].x, this->points[i].y, this->points[i].z);
                    }
                }
                else for (auto p : this->points) {
                    glVertex3d(p.x, p.y, p.z);
                }
            }
            glEnd();
        }
        for (auto ch : this->children) {
            ch->render(mLog);
        }
        glPopMatrix();
    }

    void cObject::render() {
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glTranslated(this->translation.x, this->translation.y, this->translation.z);
        glRotated(this->rotation.x, 1, 0, 0);
        glRotated(this->rotation.y, 0, 1, 0);
        glRotated(this->rotation.z, 0, 0, 1);
        glScaled(this->scale, this->scale, this->scale);
        if (!hidden) {
            glBegin(glFlag);
            {
                if (this->normals.size() == this->points.size()) {
                    for (int i = 0; i < this->points.size(); i++) {
                        glNormal3d(this->normals[i].x, this->normals[i].y, this->normals[i].z);
                        glVertex3d(this->points[i].x, this->points[i].y, this->points[i].z);
                    }
                }
                else for (auto p : this->points) {
                    glVertex3d(p.x, p.y, p.z);
                }
            }
            glEnd();
        }
        for (auto ch : this->children) {
            ch->render();
        }
        glPopMatrix();
    }

    vec3 cObject::getPoint(int index) {
        return this->points[index];
    }

    void cObject::addPoint(vec3 p) {
        this->points.push_back(p);
    }

    void cObject::addPoint(vec3 p, vec3 n) {
        this->points.push_back(p);
        this->normals.push_back(n);
    }

    void cObject::setPoint(int index, vec3 p) {
        this->points[index] = p;
    }

    void cObject::setGLFlag(uint32_t flag) {
        this->glFlag = flag;
    }

    void cObject::addChild(cObject* c) {
        this->children.push_back(c);
    }

    void cObject::setParent(cObject* p) { //Should never be needed -> Only to be abused by me later -_-
        this->parent = parent;
        p->addChild(this);
        /* Do changes to translation here*/
    }

    void cObject::setRotation(vec3 r) {
        this->rotation = r;
    }

    void cObject::setTranslation(vec3 t) {
        this->translation = t;
    }

    void cObject::setScale(double s) {
        this->scale = s;
    }

    void cObject::translate(vec3 t) {
        this->translation += t;
    }

    /* Ensure axis is either (1,0,0) (0,1,0) (0,0,1) or I will crash on you. */
    void cObject::rotate(double r, vec3 axis) {
        if (axis != vec3(1, 0, 0) && axis != vec3(0, 1, 0) && axis != vec3(0, 0, 1)) abort();
        this->rotation += vec3(axis.x*r, axis.y*r, axis.z*r);
        if (this->rotation.x > 180) this->rotation.x -= 360;
        if (this->rotation.x < -180) this->rotation.x += 360;
        if (this->rotation.y > 180) this->rotation.y -= 360;
        if (this->rotation.y < -180) this->rotation.y += 360;
        if (this->rotation.z > 180) this->rotation.z -= 360;
        if (this->rotation.z < -180) this->rotation.z += 360;
    }

    void cObject::rescale(double s) {
        this->scale += s;
    }

    void cObject::printDebug() {
        printf("Name: %s\n", this->name.c_str());
        printf("Translation: %.2f %.2f %.2f \n", this->translation.x, this->translation.y, this->translation.z);
        printf("Rotation (x, y, z): %.2f %.2f %.2f \n", this->rotation.x, this->rotation.y, this->rotation.z);
        printf("Scale: %.2f\n", this->scale);
        
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        loadMatrix();
        double mat[16];

        glGetDoublev(GL_MODELVIEW_MATRIX, mat);

        std::string debug;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                debug += std::to_string(mat[i * 4 + j]) + " ";
            }
            debug += '\n';
        }

        printf("Matrix:\n%s \n", debug.c_str());
        glPopMatrix();
    }

}