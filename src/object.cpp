#include "object.h"

/* 
Apparently opengl stores the modelview matrix as
0  4  8  12
1  5  9  13
2  6  10 14
3  7  11 15

Fuck. Everything.
*/

namespace __game__ {

    cObject::cObject() {
        this->glFlag = GL_TRIANGLE_FAN;
        this->hidden = false;
        this->translation = vec3(0, 0, 0);
        this->rotation = vec3(0, 0, 0);
        this->scale = 1;
        this->parent = NULL;
        this->hb = NULL;
        this->texID = 0;
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
        glRotated(this->rotation.z, 0, 0, 1);
        glRotated(this->rotation.y, 0, 1, 0);
        glRotated(this->rotation.x, 1, 0, 0);
        glScaled(this->scale, this->scale, this->scale);
    }

    void cObject::render(__logger::cLogger* mLog) {
        mLog->log("[object.cpp] Info: Rendering object " + this->name);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glTranslated(this->translation.x, this->translation.y, this->translation.z);
        glRotated(this->rotation.z, 0, 0, 1);
        glRotated(this->rotation.y, 0, 1, 0);
        glRotated(this->rotation.x, 1, 0, 0);
        glScaled(this->scale, this->scale, this->scale);
        if (!hidden) {
            if(this->texID != 0) glBindTexture(GL_TEXTURE_2D, this->texID);
            glBegin(glFlag);
            {
                if (this->normals.size() == this->points.size() && this->texture.size() == this->points.size()) {
                    for (int i = 0; i < this->points.size(); i++) {
                        glNormal3d(this->normals[i].x, this->normals[i].y, this->normals[i].z);
                        glTexCoord2d(this->texture[i].x, this->texture[i].y); //z is ignored because it's a 2d vector
                        glVertex3d(this->points[i].x, this->points[i].y, this->points[i].z);
                    }
                }
                else for (auto p : this->points) {
                    glVertex3d(p.x, p.y, p.z);
                }
            }
            glEnd();
            if(this->texID != 0) glBindTexture(GL_TEXTURE_2D, this->texID);
        }
        for (auto ch : this->children) {
            ch->render(mLog);
        }
        glPopMatrix();
    }

    void cObject::render() {
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        double mMat[16];
        glTranslated(this->translation.x, this->translation.y, this->translation.z);
        glRotated(this->rotation.z, 0, 0, 1);
        glRotated(this->rotation.y, 0, 1, 0);
        glRotated(this->rotation.x, 1, 0, 0);
        glScaled(this->scale, this->scale, this->scale);
        if (!hidden) {
            if(this->texID != 0) glBindTexture(GL_TEXTURE_2D, this->texID);
            glBegin(glFlag);
            {
                if (this->normals.size() == this->points.size() && this->texture.size() == this->points.size()) {
                    for (int i = 0; i < this->points.size(); i++) {
                        glTexCoord2d(this->texture[i].x, this->texture[i].y); //z is ignored because it's a 2d vector
                        glNormal3d(this->normals[i].x, this->normals[i].y, this->normals[i].z);
                        glVertex3d(this->points[i].x, this->points[i].y, this->points[i].z);
                    }
                }
                else for (auto p : this->points) {
                    glVertex3d(p.x, p.y, p.z);
                }
            }
            glEnd();
            if(this->texID != 0) glBindTexture(GL_TEXTURE_2D, 0);
        }
        for (auto ch : this->children) {
            if (ch->getName() == "Camera") continue;
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

    void cObject::addPoint(vec3 p, vec3 n, vec3 t) {
        this->points.push_back(p);
        this->normals.push_back(n);
        this->texture.push_back(t);
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
        this->parent = p;
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
        printf("Translation: %f %f %f \n", this->translation.x, this->translation.y, this->translation.z);
        printf("Rotation (x, y, z): %f %f %f \n", this->rotation.x, this->rotation.y, this->rotation.z);
        printf("Scale: %.2f\n", this->scale);
        if (this->parent != NULL) printf("Parent: %s \n", this->parent->getName().c_str());
        else printf("Parent: N/A (is root) \n");

        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        loadMatrix();
        double mat[16];

        glGetDoublev(GL_MODELVIEW_MATRIX, mat);

        std::string debug;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                debug += std::to_string(mat[i + j * 4]) + " ";
            }
            debug += '\n';
        }

        printf("Matrix:\n%s \n", debug.c_str());
        glPopMatrix();
    }

    void cObject::addTex(vec3 c) {
        this->texture.push_back(c);
    }

    void cObject::setTexID(int id) {
        this->texID = id;
    }

    void cObject::setHitBox(hitBox* in) {
        this->hb = in;
    }

    void cObject::updateHB() {
        this->hb->origin = this->translation + this->hb->originDisp;
    }

    bool cObject::collidesWith(cObject* other) {
        if (this->hb) {
            this->updateHB();
            other->updateHB();
            bool rVal = false;
            for (auto ch : this->children) {
                if (ch->collidesWith(other)) {
                    rVal = true;
                    break;
                }
            }
            return (this->hb->intersects(*(other->hb)) | rVal);
        }
        return false;
    }
}