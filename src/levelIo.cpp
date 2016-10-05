#include "game.h"

#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
#include "globals.h"

namespace __game__ {

    //TODO: Add handling errornous inputs (Currently undefined)
    sMap* cMain::loadMap(std::string inFile) {
        std::ifstream ifs(inFile);
        rapidjson::IStreamWrapper isw(ifs);

        rapidjson::Document doc;
        doc.ParseStream(isw);

        sMap* rVal = NULL;
        rVal = new sMap;
        
        /* Grab basic details */
        if (doc.HasMember("width")) rVal->width = doc["width"].GetInt();
        if (doc.HasMember("depth")) rVal->depth = doc["depth"].GetInt();
        if (doc.HasMember("sunlight")) {
            rVal->sunlight = vec3(
                doc["sunlight"][0].GetDouble(),
                doc["sunlight"][1].GetDouble(),
                doc["sunlight"][2].GetDouble()
                );
        }
        if (doc.HasMember("altitude")) {
            for (int i = 0; i < doc["altitude"].Size(); i++) {
                rVal->altitudes.push_back(doc["altitudes"][i].GetDouble());
            }
        }
        if (doc.HasMember("trees")) {
            for (int i = 0; i < doc["trees"].Size(); i++) {
                rVal->trees.push_back(std::make_pair(doc["trees"][i]["x"].GetDouble(), doc["trees"][i]["z"].GetDouble())); //Wew
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

    bool cMain::saveMap(std::string outFile) {

    }

}