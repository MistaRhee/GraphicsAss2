#include "game.h"

#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
#include "globals.h"

/* Out of ResidentSleeper L ResidentSleeper A ResidentSleeper Z ResidentSleeper I ResidentSleeper N ResidentSleeper E ResidentSleeper S ResidentSleeper S ResidentSleeper */
/* "Chunks" (blocks of altitudes) that are in view will be set to 3x3 for the moment */

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
            float globalAmb[] = { 0.2, 0.2, 0.2, 0.1 };
            glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmb);

            float localAmb[] = {0.1, 0.1, 0.1, 1};
            float localDiff[] = {1, 1, 1, 1};
            float localSpec[] = {1, 1, 1, 1};
            /* FIXME: Unfuck this shit */
            float position[] = { doc["sunlight"][0].GetDouble(), doc["sunlight"][1].GetDouble(), doc["sunlight"][2].GetDouble(), 1 };

            glLightfv(GL_LIGHT0, GL_AMBIENT, localAmb);
            glLightfv(GL_LIGHT0, GL_DIFFUSE, localDiff);
            glLightfv(GL_LIGHT0, GL_SPECULAR, localSpec);
            glLightfv(GL_LIGHT0, GL_POSITION, position);
        }
        if (doc.HasMember("altitude")) {
            std::vector<double> alts;
            for (int i = 0; i < doc["altitude"].Size(); i++) {
                alts.push_back(doc["altitudes"][i].GetDouble());
            }
            //TODO: Generate points (doing the extra vertex in the center trick)
            cObject mMap(this->ROOT);
            for (int i = 0, z = doc["width"].GetInt()-1; i < z; i++) {
                for (int j = 0, y = doc["depth"].GetInt()-1; j < y; j++) {
                    /* Add middle then the four corners */
                    mMap.addPoint();
                }
            }
        }
        if (doc.HasMember("trees")) {
            for (int i = 0; i < doc["trees"].Size(); i++) {
                this->ROOT->addChild(new cTree(doc["trees"][i]["x"].GetDouble(), doc["trees"][i]["z"].GetDouble(), ));
            }
        }
        if (doc.HasMember("roads")) {
            for (int i = 0; i < doc["roads"].Size(); i++) {
                std::vector<std::pair<double, double> > points;
                for (int j = 0; j < doc["roads"][i]["spine"].Size(); j++) {
                    points.push_back(std::make_pair(doc["roads"][i]["spine"][j].GetDouble(), doc["roads"][i]["spine"][++j].GetDouble()));
                }
                rVal->roads.push_back(cRoad(doc["roads"][i]["width"].GetDouble(), points));
            }
        }
        if (doc.HasMember("starting")) {
            rVal->startLoc = vec3(doc["starting"]["x"].GetDouble(), doc["starting"]["y"].GetDouble(), doc["starting"]["z"].GetDouble());
        }
        return rVal;
    }

}