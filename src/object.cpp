#include "object.h"

namespace __game__ {

    cObject::cObject() {
        this->glFlag = GL_TRIANGLE_FAN;
    }

    cObject::cObject(cObject* parent) {
        this->parent = parent;
    }

    cObject::cObject(vec3 t, double r, double s) {
        this->translation = t;
        this->rotation = r;
        this->scale = s;
    }

    cObject::cObject(std::vector<std::pair<double, double> > points) : cObject() {
        this->points = std::vector<std::pair<double, double> >(points);
    }

    void cObject::render() {
        glBegin(glFlag);
        {
            for (auto p : this->points) {
                glVertex2d(p.first, p.second);
            }
        }
        glEnd();
    }

    std::pair<double, double> cObject::getPoint(int index) {
        return this->points[index];
    }

    void cObject::setPoint(int index, double x, double y) {
        this->points[index] = std::make_pair(x, y);
    }

    void cObject::setGLFlag(uint32_t flag) {
        this->glFlag = flag;
    }

    void cObject::addChild(cObject* c) {
        this->children.push_back(c);
    }

    void cObject::setParent(cObject* p) {
        this->parent = parent;
        /* Do changes to translation here*/
        //TODO: Finish this
    }

    void cObject::setRotation(double r) {
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

    void cObject::rotate(double r) {
        this->rotation += r;
        if (this->rotation > 180) this->rotation -= 360;
        if (this->rotation < -180) this->rotation += 360;
    }

    void cObject::rescale(double s) {
        this->scale += s;
    }

}