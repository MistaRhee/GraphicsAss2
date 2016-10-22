#include "object.h"

double b(int i, double t) {
    switch (i) {
        case 0:
            return (1 - t) * (1 - t) * (1 - t);
        case 1:
            return 3 * (1 - t) * (1 - t) * t;
        case 2:
            return 3 * (1 - t) * t * t;
        case 3:
            return t * t * t;
        default:
            throw mException(std::string("[road.cpp] Error: Invalid i for Bezier calculation. i = ") + std::to_string(i));
    }
}

double dist(double x0, double y0, double x1, double y1) {
    return sqrt((x0 - x1)*(x0 - x1) + (y0 - y1)*(y0 - y1));
}

namespace __game__ {

    //TODO: Overload the render function and render the width of the road (or just change the add segment to have the nice little road with widths there. IDK */

    cRoad::cRoad(double width, std::vector<std::pair<double, double> > inPoints, std::vector<double> altitudes, double mapWidth) {
        this->width = width;
        setGLFlag(GL_TRIANGLE_STRIP);
        this->prevStart = inPoints[0];
		//for (unsigned int i = 0; i < inPoints.size();) {
		//	printf("i %d\n", i);
		//	printf("%f %f\n",inPoints[i].first, inPoints[i].second);
		//}
        for (unsigned int i = 1; i < inPoints.size();) {
            addSegment(inPoints[i++], inPoints[i++], inPoints[i++], altitudes, mapWidth);
        }
    }

    double cRoad::getWidth() {
        return this->width;
    }

    /* Estimate the curve with 16 points, see how good that looks */
    void cRoad::addSegment(std::pair<double, double> controla, std::pair<double, double> controlb, std::pair<double, double> end, std::vector<double> alts, double mWidth) {
		//printf("%f %f %f %f\n", prevStart.first, prevStart.second, controla.first, controla.second);
		//printf("%f %f %f %f\n", controlb.first, controlb.second, end.first, end.second);
		for (int i = 0; i < 16; i++) {
            /* Interpolate the "appropriate" height */
			double x = b(0, (double)i / 16) * prevStart.first + b(1, (double)i / 16) * end.first + b(2, (double)i / 16) * controlb.first + b(3, (double)i / 16) * controla.first;
			double z = b(0, (double)i / 16) * prevStart.second + b(1, (double)i / 16) * end.second + b(2, (double)i / 16) * controlb.second + b(3, (double)i / 16) * controla.second;
            double rx = x - floor(x);
            double rz = z - floor(z);

            double midAlt = (alts[floor(x) + floor(z)*mWidth] + alts[ceil(x) + floor(z)*mWidth] + alts[floor(x) + ceil(z)*mWidth] + alts[ceil(x) + ceil(z)*mWidth]) / 4;

            /* I'm a monster -_- */
            double y = 0.001;
            if (x > z) {
                if (x > 1 - z) {
                    y += (dist(rx, rz, 0, 1) * alts[floor(x) + ceil(z)*mWidth] + dist(rx, rz, 0.5, 0.5) * midAlt + dist(rx, rz, 1, 1) * alts[ceil(x) + ceil(z)*mWidth]) / (dist(rx, rz, 0, 1) + dist(rx, rz, 1, 1) + dist(rx, rz, 0.5, 0.5));
                }
                else {
                    y += (dist(rx, rz, 1, 0) * alts[floor(x) + ceil(z)*mWidth] + dist(rx, rz, 0.5, 0.5) * midAlt + dist(rx, rz, 1, 1) * alts[ceil(x) + ceil(z)*mWidth]) / (dist(rx, rz, 1, 0) + dist(rx, rz, 1, 1) + dist(rx, rz, 0.5, 0.5));
                }
            }
            else {
                if (x > 1 - z) {
                    y += (dist(rx, rz, 0, 1) * alts[floor(x) + ceil(z)*mWidth] + dist(rx, rz, 0.5, 0.5) * midAlt + dist(rx, rz, 0, 0) * alts[ceil(x) + ceil(z)*mWidth]) / (dist(rx, rz, 0, 1) + dist(rx, rz, 0, 0) + dist(rx, rz, 0.5, 0.5));
                }
                else {
                    y += (dist(rx, rz, 1, 0) * alts[floor(x) + ceil(z)*mWidth] + dist(rx, rz, 0.5, 0.5) * midAlt + dist(rx, rz, 0, 0) * alts[ceil(x) + ceil(z)*mWidth]) / (dist(rx, rz, 1, 0) + dist(rx, rz, 0, 0) + dist(rx, rz, 0.5, 0.5));
                }
            }
            this->points.push_back(vec3(x, y, z));
        }
        //this->prevStart = end;
    }

    //TODO: Finish this
	void cRoad::render() {
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glTranslated(this->translation.x, this->translation.y, this->translation.z);
		glRotated(this->rotation.z, 0, 0, 1);
		glRotated(this->rotation.y, 0, 1, 0);
		glRotated(this->rotation.x, 1, 0, 0);
		glScaled(this->scale, this->scale, this->scale);
		//for (int i = 0; i < this->points.size(); i++) {		//	printf("%d, %f, %f, %f,\n", i, this->points[i].x, this->points[i].y, this->points[i].z);		//}
		double h = 2; //substitute with altitude
		double width = 2;
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glBegin(GL_QUAD_STRIP);
		for (int i = 0; i < this->points.size(); i++) {
			//glVertex3d(this->points[i].x, this->points[i].y, this->points[i].z);
			vec3 backpoint;
			vec3 frontpoint;
			if (i != 0) {
				backpoint = this->points[i - 1];
			}
			else {
				backpoint = this->points[i];
			}			if (i != this->points.size() - 1) {
				frontpoint = this->points[i + 1];
			}			else {				frontpoint = this->points[i];
			}
			double perpx = (frontpoint.x - backpoint.x);
			double perpz = (frontpoint.z - backpoint.z);
			double norm = sqrt(perpx*perpx + perpz*perpz);
			vec3 perpvec(perpz / norm, backpoint.y, -perpx / norm);
			glNormal3d(0, 1, 0);
			//printf("%f %f %f\n", perpvec.x*width / 2 + this->points[i].x, this->points[i].y, perpvec.z*width / 2 + this->points[i].z);
			glVertex3d(perpvec.x*width / 2 + this->points[i].x, this->points[i].y, perpvec.z*width / 2 + this->points[i].z);

			glNormal3d(0, 1, 0);
			//printf("%f %f %f\n", -perpvec.x*width / 2 + this->points[i].x, this->points[i].y, -perpvec.z*width / 2 + this->points[i].z);
			glVertex3d(-perpvec.x*width / 2 + this->points[i].x, this->points[i].y, -perpvec.z*width / 2 + this->points[i].z);
		}
		glEnd();
		glPopMatrix();
	}
}