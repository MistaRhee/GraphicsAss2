#pragma once

#include <cstdio>
#include <cstdlib>
#include <string>


#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_ttf.h>

#include "logger.hpp"

namespace __game__ {

    class cMain {
    public:
        cMain(int argc, char** argv);
        ~cMain();

        void run();
    private:
        /* Initialization functions */
        void initSDL();
        void destroySDL();
        void initGL();
        void destroyGL();

        void parseArgs(int, char**);

        /* Game loop functions */
        void update();
        void render();
        void processEvents();
        void handleUserKeyboard();
        void handleUserMouse();
        void sudoku();

        bool isAlive;

        /* Error handling */
        /* Debug level < 0 is no log */
        void debugError(std::string); //DebugLevel = 0
        void debugWarning(std::string); //DebugLevel = 1
        void debugInformation(std::string); //DebugLevel = 2 (pedantic)
        __logger::cLogger* mLog;
        uint8_t debugLevel;

        /* Window storage */
        SDL_Window* mWindow;
        SDL_GLContext mContext;
    };
}