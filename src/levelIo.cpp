#include "game.h"

#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
#include "globals.h"

/* Out of ResidentSleeper L ResidentSleeper A ResidentSleeper Z ResidentSleeper I ResidentSleeper N ResidentSleeper E ResidentSleeper S ResidentSleeper S ResidentSleeper */
/* "Chunks" (blocks of altitudes) that are in view will be set to 3x3 for the moment */

/*
   x0   x1   x2   x3   x4
z0 0    1    1    1    2
z1 0    1    2    3    2
z2 0    1    1    2    3
z3 0    1    1    1    2
z4 0    1    1    1    1

*/

inline double dist(double x0, double y0, double x1, double y1) {
    return sqrt((x0 - x1)*(x0 - x1) + (y0 - y1)*(y0 - y1));
}

namespace __game__ {

    //TODO: Add handling errornous inputs (Currently undefined)
    void cMain::loadMap(std::string inFile) {
        std::ifstream ifs(inFile);
        rapidjson::IStreamWrapper isw(ifs);

        rapidjson::Document doc;
        doc.ParseStream(isw);

        /* Grab basic details */
        if (doc.HasMember("width")) this->width = doc["width"].GetInt();
        if (doc.HasMember("depth")) this->depth = doc["depth"].GetInt();
        if (doc.HasMember("sunlight")) {
            this->sunlight = vec3(doc["sunlight"][0].GetFloat(), doc["sunlight"][1].GetFloat(), doc["sunlight"][2].GetFloat());
        }
        if (doc.HasMember("altitude")) {
            const rapidjson::Value& alt = doc["altitude"];
            for (unsigned int i = 0; i < alt.Size(); i++) {
                altitudes.push_back(alt[i].GetDouble());
            }
            cMap* mMap = new cMap(this->ROOT);
            mMap->setName("mMap");
            mMap->setTexID(this->textures[0]);
            for (int i = 0; i < width - 1; i++) {
                for (int j = 0; j < depth - 1; j++) {
                    /* Add middle then the four corners */
                    mMap->addPoint(vec3(i + 0.5, (altitudes[i + j*width] + altitudes[i + 1 + j*(width)] + altitudes[i + (j + 1)*(width)] + altitudes[i + 1 + (j + 1)*(width)]) / 4, (j + 0.5))); //Middle point is interpolated from the corners
                    mMap->addPoint(vec3(i, altitudes[i + j*(width)], j));
                    mMap->addPoint(vec3(i + 1, altitudes[i + 1 + j*(width)], j));
                    mMap->addPoint(vec3(i, altitudes[i + (j + 1)*(width)], (j + 1)));
                    mMap->addPoint(vec3(i + 1, altitudes[i + 1 + (j + 1)*(width)], (j + 1)));
                }
            }
        }
        if (doc.HasMember("trees")) {
            const rapidjson::Value& tree = doc["trees"];
            for (unsigned int i = 0; i < tree.Size(); i++) {
                double x = tree[i]["x"].GetDouble();
                double z = tree[i]["z"].GetDouble();
                int fx = floor(x);
                int fz = floor(z);
                int cx = ceil(x);
                int cz = ceil(z);
                cTree* mTree = new cTree(
                    x, z,
                    std::max(
                        altitudes[fx + fz*width],
                        std::max(
                            altitudes[fx + cz*width],
                            std::max(
                                altitudes[cx + fz*width],
                                altitudes[cx + cz*width]
                            )
                        )
                    ), //min height is the max of the 4 points around it
                    this->textures[0]
                );
                mTree->setName("Tree");
                this->ROOT->addChild(mTree);
                /* Side note: Definitely not bad code right? ... right? */
            }
        }
        if (doc.HasMember("roads")) {
            for (unsigned int i = 0; i < doc["roads"].Size(); i++) {
                std::vector<std::pair<double, double> > points;
                for (unsigned int j = 0; j < doc["roads"][i]["spine"].Size(); j++) {
                    double x = doc["roads"][i]["spine"][j++].GetDouble();
                    double z = doc["roads"][i]["spine"][j].GetDouble();
                    points.push_back(std::make_pair(x, z));;
                }
                cRoad* mRoad = new cRoad(doc["roads"][i]["width"].GetDouble(), points, altitudes, width);
                mRoad->setName("road");
                this->ROOT->addChild(mRoad);
            }
        }

        if (doc.HasMember("bush")) {
            double x, y, z;
            x = doc["bush"]["x"].GetDouble();
            z = doc["bush"]["z"].GetDouble();
            cBush* b = new cBush(x, z);
            y = 0;
            double rx = x - floor(x);
            double rz = z - floor(z);

            double midAlt = (altitudes[floor(x) + floor(z)*width] + altitudes[ceil(x) + floor(z)*width] + altitudes[floor(x) + ceil(z)*width] + altitudes[ceil(x) + ceil(z)*width]) / 4;
            if (x > z) {
                if (x > 1 - z) {
                    y += (dist(rx, rz, 0, 1) * altitudes[floor(x) + ceil(z)*width] + dist(rx, rz, 0.5, 0.5) * midAlt + dist(rx, rz, 1, 1) * altitudes[ceil(x) + ceil(z)*width]) / (dist(rx, rz, 0, 1) + dist(rx, rz, 1, 1) + dist(rx, rz, 0.5, 0.5));
                }
                else {
                    y += (dist(rx, rz, 1, 0) * altitudes[floor(x) + ceil(z)*width] + dist(rx, rz, 0.5, 0.5) * midAlt + dist(rx, rz, 1, 1) * altitudes[ceil(x) + ceil(z)*width]) / (dist(rx, rz, 1, 0) + dist(rx, rz, 1, 1) + dist(rx, rz, 0.5, 0.5));
                }
            }
            else {
                if (x > 1 - z) {
                    y += (dist(rx, rz, 0, 1) * altitudes[floor(x) + ceil(z)*width] + dist(rx, rz, 0.5, 0.5) * midAlt + dist(rx, rz, 0, 0) * altitudes[ceil(x) + ceil(z)*width]) / (dist(rx, rz, 0, 1) + dist(rx, rz, 0, 0) + dist(rx, rz, 0.5, 0.5));
                }
                else {
                    y += (dist(rx, rz, 1, 0) * altitudes[floor(x) + ceil(z)*width] + dist(rx, rz, 0.5, 0.5) * midAlt + dist(rx, rz, 0, 0) * altitudes[ceil(x) + ceil(z)*width]) / (dist(rx, rz, 1, 0) + dist(rx, rz, 0, 0) + dist(rx, rz, 0.5, 0.5));
                }

                b->setHeight(y);
                this->ROOT->addChild(b);
            }
            /* Default start at 0, 0, h, where h is the altitude of 0, 0*/
        }
    }
}