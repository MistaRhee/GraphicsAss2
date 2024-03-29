#pragma once

#include <fstream>
#include <cstdlib>
#include <string>


#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_ttf.h>

#include "logger.hpp"
#include "actor.h"
#include "pawn.h"
#include "object.h"

#define GAME_WINDOW_WIDTH 1280
#define GAME_WINDOW_HEIGHT 720

namespace __game__ {

    class cMain {
    public:
        cMain(int argc, char** argv);
        ~cMain();

        void run();

        cObject* ROOT;//Is the root object. Stay safe young one

    private: //Commented out because gosh darned it I have to write bad code. Don't do this at home kids.
        /* Initialization */
        void initSDL();
        void destroySDL();
        void initGL();
        void destroyGL();

        void parseArgs(int, char**);

        /* Level I/O */
        void loadMap(std::string); //HACK: just for the purposes of this assignment

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

        /* Actor storage */
        cCamera* mCamera; //Will always have a value. For quick access for third person
        cPawn* currPawn; //If not assigned, then free camera which can fly through. Rapid collision detection stuffs ECKS DEE
        std::vector<cActor*> mActors;
        std::vector<cPortal*> mPortals;

        /* Assignment specific shit which I'll probably say is TERRIBLE */
        vec3 sunlight;
        std::vector<double> altitudes;
        GLuint* textures;
        const int maxText = 1;

        /* Window storage */
        SDL_Window* mWindow;
        SDL_GLContext mContext;

        /* Current map storage data */
        int width;
        int depth;
    };
}