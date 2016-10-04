#include "game.h"

#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"

namespace __game__ {

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
    }

    bool cMain::saveMap(std::string outFile) {

    }

}