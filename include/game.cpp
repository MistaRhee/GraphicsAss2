#include "game.h"

namespace __game__ {

    cMain::cMain(int argc, char** argv) {
        this->debugLevel = 0;
        this->isAlive = true;
        this->mWindow = NULL;
        this->mContext = NULL;
        this->currPawn = NULL;
        
        this->mCamera = new cCamera(NULL, vec3(0, 0, 0), 0, 0); 

        parseArgs(argc, argv);

        this->mLog = new __logger::cLogger("logs/game.log");
        this->mLog->start();

        initSDL();
        initGL();
    }

    cMain::~cMain() {
        destroyGL();
        destroySDL();
        this->mLog->kill();
        this->mLog->done.lock();
        this->mLog->done.unlock();
    }

    void cMain::debugError(std::string e) {
        if (this->debugLevel < 0) return;
        this->mLog->log(e);
        SDL_ShowSimpleMessageBox(
            SDL_MESSAGEBOX_ERROR,
            "Error",
            "An error has occured. Check the logs, program will now die.",
            NULL
            );
        exit(2); //Error exit
    }

    void cMain::debugWarning(std::string e) {
        if (this->debugLevel < 1) return;
        this->mLog->log(e);
    }

    void cMain::debugInformation(std::string e) {
        if (this->debugLevel < 2) return;
        this->mLog->log(e);
    }

    void cMain::parseArgs(int argc, char** argv) {
        for (int i = 1; i < argc; i++) {
            for (int j = 0, k = strlen(argv[i]); j < k; j++) {
                if (argv[i][j] == 'v') {
                    this->debugLevel++;
                }
                if (argv[i][j] == 'c') {
                    this->debugLevel = -1;
                    return; //I really am lazy -_-
                }
            }
        }
    }

    void cMain::initSDL() {
        if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
            this->debugError(std::string("[game.cpp] Error: Failed to load SDL! SDL_Error: ") + std::string(SDL_GetError()));
        }
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
        this->mWindow = SDL_CreateWindow(
            "3421 Second Assignment",
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT,
            SDL_WINDOW_OPENGL
            );
        if (this->mWindow == NULL) {
            this->debugError(std::string("[game.cpp] Error: Failed to crete window! SDL_Error: ") + std::string(SDL_GetError()));
        }
    }

    void cMain::initGL() {
        this->mContext = SDL_GL_CreateContext(mWindow);
        if (mContext == NULL) {
            this->debugError(std::string("[game.cpp] Error: OpenGL Context couldn't be created! SDL_Error: ") + std::string(SDL_GetError()));
        }

        if (SDL_GL_SetSwapInterval(0) < 0) {
            this->debugWarning(std::string("[game.cpp] Warning: Unable to set swap interval to 0. SDL_Error: ") + std::string(SDL_GetError()));
        }

        GLenum err = GL_NO_ERROR;
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        /* Set the perspective camera. */
//TODO: Tweak numbers to make stuff look pretty
        gluPerspective(100, GAME_WINDOW_WIDTH/GAME_WINDOW_HEIGHT, 0, 10);

        err = glGetError();
        if (err != GL_NO_ERROR) {
            this->debugError(std::string("[game.cpp] Error: Failed to initialize OpenGL. Error: ") + std::string(reinterpret_cast<const char*>(glewGetErrorString(err))));
        }

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        err = glGetError();
        if (err != GL_NO_ERROR) {
            this->debugError(std::string("[game.cpp] Error: Failed to initialize OpenGL. Error: ") + std::string(reinterpret_cast<const char*>(glewGetErrorString(err))));
        }

        glClearColor(0.f, 0.f, 0.f, 1.f); //Black clear colour
        err = glGetError();
        if (err != GL_NO_ERROR) {
            this->debugError(std::string("[game.cpp] Error: Failed to initialize OpenGL. Error: ") + std::string(reinterpret_cast<const char*>(glewGetErrorString(err))));
        }

        /* Back face culling */
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        err = glGetError();
        if (err != GL_NO_ERROR) {
            this->debugError(std::string("[game.cpp] Error: Failed to initialize OpenGL. Error: ") + std::string(reinterpret_cast<const char*>(glewGetErrorString(err))));
        }

        /* Enable depth testing */
        glEnable(GL_DEPTH_TEST);
        err = glGetError();
        if (err != GL_NO_ERROR) {
            this->debugError(std::string("[game.cpp] Error: Failed to initialize OpenGL. Error: ") + std::string(reinterpret_cast<const char*>(glewGetErrorString(err))));
        }

        glEnable(GL_LIGHTING);
        err = glGetError();
        if (err != GL_NO_ERROR) {
            this->debugError(std::string("[game.cpp] Error: Failed to initialize OpenGL. Error: ") + std::string(reinterpret_cast<const char*>(glewGetErrorString(err))));
        }

        glEnable(GL_LIGHT0); //Will be used for sunlight, specific point lights will have to wait.
    }

    void cMain::destroyGL() {
        SDL_GL_DeleteContext(this->mContext);
    }

    void cMain::destroySDL() {
        SDL_DestroyWindow(this->mWindow);
        SDL_Quit();
    }

    void cMain::sudoku() {
        this->isAlive = false;
    }

    void cMain::run() {
        uint32_t startTime = SDL_GetTicks();
        const uint32_t FRAME_CAP = 60 / 1000; //Fixed at 60 FPS 'cus I'm too lazy to do frame independant movement (Bethesda-esqe movement)

        while (this->isAlive) {
            update();
            processEvents();
            render();
            if ((SDL_GetTicks() - startTime) < FRAME_CAP) SDL_Delay(abs((int)(FRAME_CAP - SDL_GetTicks() + startTime)));
        }
    }

    void cMain::render() {
        /* Clear screen */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        /* Begin rendering components */
        if (this->mCamera != NULL) this->mCamera->render();
        if (this->mMap != NULL) renderMap(this->mMap);
        if (this->currPawn != NULL) this->currPawn->render();
        for (auto it : this->mActors) {
            it.second->render();
        }
        /* End rendering components */
        /* Update the screen */
        SDL_GL_SwapWindow(this->mWindow);
    }

    void cMain::update() {
        /* Stub ATM */
        for (auto it : this->mActors) {
            it.second->update();
        }
    }

    void cMain::renderMap(sMap* mMap) {

    }
}