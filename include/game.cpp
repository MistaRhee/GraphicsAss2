#include "game.h"


namespace __game__ {
    cMain::cMain(int argc, char** argv) {
        this->debugLevel = 0;
        this->isAlive = true;
        this->mWindow = NULL;
        this->mContext = NULL;

        parseArgs(argc, argv);

        this->mLog = new __logger::cLogger();

        initSDL();
        initGL();
    }

    cMain::~cMain() {
        destroyGL();
        destroySDL();
    }

    void cMain::initSDL() {
        if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
            this->mLog->log("[game.cpp] Error: Failed to load SDL! SDL_Error: " + std::string(SDL_GetError()));
            exit(-1);
        }
    }

    void cMain::sudoku() {
        this->isAlive = false;
    }
}