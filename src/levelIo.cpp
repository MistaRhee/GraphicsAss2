#include "game.h"

#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"

namespace __game__ {

    //TODO: Add handling errornous inputs (Currently undefined)
    sMap* cMain::loadMap(std::string inFile) {
        std::ifstream ifs(inFile);
        rapidjson::IStreamWrapper isw(ifs);

        rapidjson::Document doc;
        doc.ParseStream(isw);

        sMap* rVal = NULL;
        rVal = new sMap();
        
        /* Grab basic details */
        if (doc.HasMember("width")) rVal->width = doc["width"].GetInt();
        if (doc.HasMember("depth")) rVal->depth = doc["depth"].GetInt();
        if (doc.HasMember("sunlight")) {
            rVal->sunlight[0] = doc["sunlight"][0].GetInt();
            rVal->sunlight[1] = doc["sunlight"][1].GetInt();
            rVal->sunlight[2] = doc["sunlight"][2].GetInt();
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
            }
        }
    }

    bool cMain::saveMap(std::string outFile) {

    }

}