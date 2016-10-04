#include "game.h"

#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"

namespace __game__ {

    void cMain::loadMap(std::string inFile) {
        std::ifstream ifs(inFile);
        rapidjson::IStreamWrapper isw(ifs);

        rapidjson::Document doc;
        doc.ParseStream(isw);

        /* Grab basic details */

    }

    bool cMain::saveMap(std::string outFile) {

    }

}