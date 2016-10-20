#include "game.h"

namespace __game__ {

    cMain::cMain(int argc, char** argv) {
        this->debugLevel = 0;
        this->isAlive = true;
        this->mWindow = NULL;
        this->mContext = NULL;
        this->currPawn = NULL;

        this->mLog = new __logger::cLogger("logs/game.log");
        this->mLog->start().detach();
        this->mLog->log(std::string("[game.cpp] System: Logging started."));

        initSDL();
        initGL();
        
        this->ROOT = new cObject();
        this->ROOT->setName("ROOT");
        this->ROOT->hidden = true;
        this->mCamera = new cCamera(this->ROOT, vec3(0, 0, 0), vec3(0, 0, 0), 1); 
        this->mCamera->setName("Camera");

        this->mActors.insert(std::make_pair("Camera", this->mCamera));

        parseArgs(argc, argv);
    }

    cMain::~cMain() {
        destroyGL();
        destroySDL();
        this->mLog->log("[game.cpp] System: Killing log.");
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
        this->debugInformation("[game.cpp] Info: Initializing SDL");
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
        this->debugInformation("[game.cpp] Info: Finished initializing SDL");
    }

    void cMain::initGL() {
        this->debugInformation("[game.cpp] Info: Initializing GL");
        this->mContext = SDL_GL_CreateContext(mWindow);
        if (mContext == NULL) {
            this->debugError(std::string("[game.cpp] Error: OpenGL Context couldn't be created! SDL_Error: ") + std::string(SDL_GetError()));
        }

        if (SDL_GL_SetSwapInterval(0) < 0) {
            this->debugWarning(std::string("[game.cpp] Warning: Unable to set swap interval to 0. SDL_Error: ") + std::string(SDL_GetError()));
        }

        GLenum err = GL_NO_ERROR;
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glMatrixMode(GL_PROJECTION);
        /* Set the perspective camera. */
        glLoadIdentity();
//TODO: Tweak numbers to make stuff look pretty
        gluPerspective(100, GAME_WINDOW_WIDTH/GAME_WINDOW_HEIGHT, 0.3, 5); //Can see two "chunks" above

        err = glGetError();
        if (err != GL_NO_ERROR) {
            this->debugError(std::string("[game.cpp] Error: Failed to initialize OpenGL 0. Error: ") + std::to_string(err));//+ std::string(reinterpret_cast<const char*>(glewGetErrorString(err))));
        }

        glMatrixMode(GL_MODELVIEW);

        err = glGetError();
        if (err != GL_NO_ERROR) {
            this->debugError(std::string("[game.cpp] Error: Failed to initialize OpenGL 1. Error: ") + std::string(reinterpret_cast<const char*>(glewGetErrorString(err))));
        }

        glClearColor(0.f, 0.f, 0.f, 1.f); //Black clear colour
        err = glGetError();
        if (err != GL_NO_ERROR) {
            this->debugError(std::string("[game.cpp] Error: Failed to initialize OpenGL 2. Error: ") + std::string(reinterpret_cast<const char*>(glewGetErrorString(err))));
        }

        /* Back face culling */
        //glEnable(GL_CULL_FACE);
        //glCullFace(GL_BACK);
        err = glGetError();
        if (err != GL_NO_ERROR) {
            this->debugError(std::string("[game.cpp] Error: Failed to initialize OpenGL 3. Error: ") + std::string(reinterpret_cast<const char*>(glewGetErrorString(err))));
        }

        /* Enable depth testing */
        glEnable(GL_DEPTH_TEST);
        err = glGetError();
        if (err != GL_NO_ERROR) {
            this->debugError(std::string("[game.cpp] Error: Failed to initialize OpenGL 4. Error: ") + std::string(reinterpret_cast<const char*>(glewGetErrorString(err))));
        }

        glEnable(GL_LIGHTING);
        err = glGetError();
        if (err != GL_NO_ERROR) {
            this->debugError(std::string("[game.cpp] Error: Failed to initialize OpenGL 5. Error: ") + std::string(reinterpret_cast<const char*>(glewGetErrorString(err))));
        }

        glEnable(GL_LIGHT0); //Will be used for sunlight, specific point lights will have to wait.
        err = glGetError();
        if (err != GL_NO_ERROR) {
            this->debugError(std::string("[game.cpp] Error: Failed to initialize OpenGL 6. Error: ") + std::string(reinterpret_cast<const char*>(glewGetErrorString(err))));
        }

        glEnable(GL_NORMALIZE);
        err = glGetError();
        if (err != GL_NO_ERROR) {
            this->debugError(std::string("[game.cpp] Error: Failed to initialize OpenGL 7. Error: ") + std::string(reinterpret_cast<const char*>(glewGetErrorString(err))));
        }

        this->debugInformation("[game.cpp] Info: Finished initializing GL");
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
        this->debugInformation("[game.cpp] Info: Loading map");
        loadMap("system/maps/test1.map");
        uint32_t startTime = SDL_GetTicks();
        const uint32_t FRAME_CAP = 60 / 1000; //Fixed at 60 FPS 'cus I'm too lazy to do frame independant movement (Bethesda-esqe movement)

        this->debugInformation("[game.cpp] Info: Starting game loop");
        while (this->isAlive) {
            update();
            processEvents();
            render();
            if ((SDL_GetTicks() - startTime) < FRAME_CAP) SDL_Delay(abs((int)(FRAME_CAP - SDL_GetTicks() + startTime)));
        }
        this->debugInformation("[game.cpp] Info: Exiting game loop");
    }

    void cMain::render() {
        /* Clear screen */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        /* Begin rendering components */
        /* Reset the matrix, just in case I pull a full retard */
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        /* KappaPride */
        
        this->mCamera->render();

        if(this->debugLevel < 2) this->ROOT->render();
        else this->ROOT->render(this->mLog);
        /* End rendering components */
        /* Update the screen */
        SDL_GL_SwapWindow(this->mWindow);
    }

    void cMain::update() {
        for (auto it : this->mActors) {
            it.second->update();
        }
    }

}