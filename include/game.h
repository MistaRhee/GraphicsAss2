#pragma once

#include <fstream>
#include <cstdlib>
#include <string>


#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_ttf.h>

#include "logger.hpp"
#include "map.h"
#include "actor.h"
#include "pawn.h"
#include "object.h"

#define GAME_WINDOW_WIDTH 800
#define GAME_WINDOW_HEIGHT 600

namespace __game__ {

    class cMain {
    public:
        cMain(int argc, char** argv);
        ~cMain();

        void run();
    private:
        /* Initialization */
        void initSDL();
        void destroySDL();
        void initGL();
        void destroyGL();

        void parseArgs(int, char**);

        /* Game loop */
        void update();
        void render();
        void processEvents();
        void handleUserKeyboard(SDL_Keycode, bool, uint32_t);
        void handleUserMouse(int, int, int, bool);
        void handleUserScroll(int, int);
        void sudoku();

        bool isAlive;
        long prevTickCount;

        /* Error handling */
        /* Debug level < 0 is no log */
        void debugError(std::string); //DebugLevel = 0
        void debugWarning(std::string); //DebugLevel = 1
        void debugInformation(std::string); //DebugLevel = 2 (pedantic)
        __logger::cLogger* mLog;
        uint8_t debugLevel;

        /* Level I/O */
        sMap* loadMap(std::string);

        /* Map storage */
        void renderMap(sMap*);
        sMap* mMap;

        /* Actor storage */
        cCamera* mCamera; //Will always have a value
        cPawn* currPawn; //If not assigned, then free camera which can fly through 
        std::map<std::string, cActor*> mActors; //Actor storage (named for ease of access)

        /* Window storage */
        SDL_Window* mWindow;
        SDL_GLContext mContext;
    };
}