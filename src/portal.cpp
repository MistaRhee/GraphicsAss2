#include "object.h"
inline double to_degrees(double radians) {
    return radians * (180.0 / M_PI);
}
namespace __game__ {

    cPortal::cPortal(std::pair<vec3, vec3> loc, double height, std::vector<double> altitudes, double width) {
        this->height = height;
        this->location = loc;
        vec3 v = loc.first - loc.second;
        this->perp = vec3(-v.y, v.x, 0);
        setHeight(altitudes, width);

        vec3 norm = (vec3(loc.first.x, 0, loc.first.y) - vec3(loc.second.x, 0, loc.second.y)) * (vec3(loc.second.x, height, loc.second.y) - vec3(loc.second.x, 0, loc.second.y));
        this->setGLFlag(GL_QUADS);
        this->addPoint(vec3(loc.first.x, 0, loc.first.y), norm, vec3((double)445 / 512, (double)45 / 512, 0));
        this->addPoint(vec3(loc.second.x, 0, loc.second.y), norm, vec3((double)445 / 512, (double)45 / 512, 0));
        this->addPoint(vec3(loc.second.x, height + this->translation.y, loc.second.y), norm, vec3((double)445 / 512, (double)45 / 512, 0));
        this->addPoint(vec3(loc.first.x, height + this->translation.y, loc.first.y), norm, vec3((double)445 / 512, (double)45 / 512, 0));

        this->addPoint(vec3(loc.first.x, height + this->translation.y, loc.first.y), norm, vec3((double)445 / 512, (double)45 / 512, 0));
        this->addPoint(vec3(loc.second.x, height + this->translation.y, loc.second.y), norm, vec3((double)445 / 512, (double)45 / 512, 0));
        this->addPoint(vec3(loc.second.x, 0, loc.second.y), norm, vec3((double)445 / 512, (double)45 / 512, 0));
        this->addPoint(vec3(loc.first.x, 0, loc.first.y), norm, vec3((double)445 / 512, (double)45 / 512, 0));
    }

    bool cPortal::collidesWith(cObject* c) {
        return false;
    }

    void cPortal::addPartner(cPortal* p) {
        this->partner = p;
    }

    void cPortal::teleport(cObject* c) {
        double angleDiff = to_degrees(acos(this->perp.dot(this->partner->perp)));
        printf("%f \n", angleDiff);
        c->rotate(angleDiff, vec3(0, 1, 0));
        c->setTranslation(vec3((this->partner->location.first.x + this->partner->location.second.x) / 2 + 0.1, 0, (this->partner->location.first.y + this->partner->location.second.y) / 2 + 0.1));
    }

    void cPortal::setHeight(std::vector<double> altitudes, double width) {
        double h = std::max(
            altitudes[this->location.first.x + this->location.first.y*width],
            altitudes[this->location.second.x + this->location.second.y*width]
        );
        this->translation.y = h;
    }

    bool cPortal::passes(vec3 p) {
        if (
            (p.x < location.first.x + 0.05 && p.x > location.second.x - 0.05) ||
            (p.x > location.first.x - 0.05 && p.x < location.second.x + 0.05)
            ) {
            if (
                (p.z < location.first.y + 0.05 && p.z > location.second.y - 0.05) ||
                (p.z > location.first.y + 0.05 && p.z < location.second.y - 0.05)
                ) {
                return true;
            }
        }
        return false;
    }

}