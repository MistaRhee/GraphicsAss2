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
            //TODO: Tweak numbers to make it look good.
            float globalAmb[] = { 0.2f, 0.2f, 0.2f, 0.1f };
            glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmb);

            float localAmb[] = {0.1f, 0.1f, 0.1f, 1.0f};
            float localDiff[] = {1.0f, 1.0f, 1.0f, 1.0f};
            float localSpec[] = {1.0f, 1.0f, 1.0f, 1.0f};
            /* FIXME: Unfuck this shit */
            float position[] = { doc["sunlight"][0].GetFloat(), doc["sunlight"][1].GetFloat(), doc["sunlight"][2].GetFloat(), 1.0f };

            glLightfv(GL_LIGHT0, GL_AMBIENT, localAmb);
            glLightfv(GL_LIGHT0, GL_DIFFUSE, localDiff);
            glLightfv(GL_LIGHT0, GL_SPECULAR, localSpec);
            glLightfv(GL_LIGHT0, GL_POSITION, position);
        }
        std::vector<double> alts; //HACKS!!!
        if (doc.HasMember("altitude")) {
            for (unsigned int i = 0; i < doc["altitude"].Size(); i++) {
                alts.push_back(doc["altitudes"][i].GetDouble());
            }
            //TODO: Generate points (doing the extra vertex in the center trick)
            cObject mMap(this->ROOT);
            for (int i = 0, z = doc["width"].GetInt()-1; i < z; i++) {
                for (int j = 0, y = doc["depth"].GetInt()-1; j < y; j++) {
                    /* Add middle then the four corners */
                    mMap.addPoint(vec3(i+0.5, (alts[i+j*z] + alts[i+1+j*z] + alts[i+(j+1)*z] + alts[i+1+(j+1)*z])/4, j+0.5)); //Middle point is interpolated from the corners
                    mMap.addPoint(vec3(i, alts[i+j*z], j));
                    mMap.addPoint(vec3(i+1, alts[i+1+j*z], j));
                    mMap.addPoint(vec3(i, alts[i+(j+1)*z], j+1));
                    mMap.addPoint(vec3(i+1, alts[i+1+(j+1)*z], j+1));
                }
            }
        }
        if (doc.HasMember("trees")) {
            for (unsigned int i = 0; i < doc["trees"].Size(); i++) {
                int fx = floor(doc["trees"][i]["x"].GetDouble());
                int fz = floor(doc["trees"][i]["z"].GetDouble());
                int cx = ceil(doc["trees"][i]["x"].GetDouble());
                int cz = ceil(doc["trees"][i]["z"].GetDouble());
                int width = doc["width"].GetInt();
                this->ROOT->addChild(new cTree(doc["trees"][i]["x"].GetDouble(), doc["trees"][i]["z"].GetDouble(),
                                               std::max(
                                                   alts[fx + fz*width],
                                                   std::max(
                                                       alts[fx + cz*width],
                                                       std::max(
                                                           alts[cx + fx*width],
                                                           alts[cx + cz*width]
                                                           )
                                                       )
                                                   ) //min height is the max of the 4 points around it
                                               ));
                /* Side note: Definitely not bad code right? ... right? */
            }
        }
        if (doc.HasMember("roads")) {
            for (unsigned int i = 0; i < doc["roads"].Size(); i++) {
                std::vector<std::pair<double, double> > points;
                for (unsigned int j = 0; j < doc["roads"][i]["spine"].Size(); j++) {
                    points.push_back(std::make_pair(doc["roads"][i]["spine"][j].GetDouble(), doc["roads"][i]["spine"][++j].GetDouble()));
                }
                this->ROOT->addChild(new cRoad(doc["roads"][i]["width"].GetDouble(), points, alts, width));
            }
        }
        /* Default start at 0, 0, h, where h is the altitude of 0, 0*/
    }
}