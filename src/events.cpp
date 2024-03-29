#include "game.h"

#define GAME_MOUSE_MOVE -1

namespace __game__ {

    void cMain::processEvents() {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_KEYDOWN:
                    handleUserKeyboard(
                        e.key.keysym.sym,
                        e.key.type == SDL_KEYDOWN,
                        e.key.keysym.mod
                    );
                    break;

                case SDL_KEYUP:
                    handleUserKeyboard(
                        e.key.keysym.sym,
                        e.key.type == SDL_KEYDOWN,
                        e.key.keysym.mod
                    );
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    handleUserMouse(
                        e.button.x,
                        e.button.y,
                        e.button.button,
                        e.button.type == SDL_MOUSEBUTTONDOWN
                    );
                    break;

                case SDL_MOUSEBUTTONUP:
                    handleUserMouse(
                        e.button.x,
                        e.button.y,
                        e.button.button,
                        e.button.type == SDL_MOUSEBUTTONDOWN
                    );
                    break;

                case SDL_MOUSEWHEEL:
                    handleUserScroll(
                        e.wheel.x,
                        e.wheel.y
                    );
                    break;

                case SDL_MOUSEMOTION:
                    handleUserMouse(
                        e.motion.xrel,
                        e.motion.yrel,
                        GAME_MOUSE_MOVE,
                        0 //Ignored anyway because no button is found
                    );
                    break;

                case SDL_QUIT:
                    sudoku(); //I'm sorry I failed you QQ
                    break;

                default:
                    /* Not handling other events at the moment */
                    break;
            }
        }
    }

    void cMain::handleUserKeyboard(SDL_Keycode key, bool isDown, uint32_t modifiers) { //Too lazy to implement frame-independent movement.
        /* Hardcoding in the movement keys ATM due to laziness */
        switch (key) {
            case SDLK_w:
                if (this->currPawn == NULL) {
                    if (isDown) this->mCamera->move(vec3(0, 0, 0.001));
                    else this->mCamera->setSpeed(vec3(0, 0, 0));
                }
                else {
                    if (isDown) this->currPawn->move(vec3(0, 0, 0.001));
                    else this->currPawn->setSpeed(vec3(0, 0, 0));
                }
                break;

            case SDLK_s:
                if (this->currPawn == NULL) {
                    if (isDown) this->mCamera->move(vec3(0, 0, -0.001));
                    else this->mCamera->setSpeed(vec3(0, 0, 0));
                }
                else {
                    if (isDown) this->currPawn->move(vec3(0, 0, -0.001));
                    else this->currPawn->setSpeed(vec3(0, 0, 0));
                }
                break;

            case SDLK_a:
                if (this->currPawn == NULL) {
                    if (isDown) this->mCamera->move(vec3(0.001, 0, 0));
                    else this->mCamera->setSpeed(vec3(0, 0, 0));
                }
                else {
                    if (isDown) this->currPawn->move(vec3(0.001, 0, 0));
                    else this->currPawn->setSpeed(vec3(0, 0, 0));
                }
                break;

            case SDLK_d:
                if (this->currPawn == NULL) {
                    if (isDown) this->mCamera->move(vec3(-0.001, 0, 0));
                    else this->mCamera->setSpeed(vec3(0, 0, 0));
                }
                else {
                    if (isDown) this->currPawn->move(vec3(-0.001, 0, 0));
                    else this->currPawn->setSpeed(vec3(0, 0, 0));
                }
                break;

            case SDLK_LSHIFT: //Pawn can't fly
                if (this->currPawn == NULL) {
                    if (isDown) this->mCamera->move(vec3(0, 0.001, 0));
                    else this->mCamera->setSpeed(vec3(0, 0, 0));
                }
                break;

            case SDLK_RSHIFT: //Porn also can't fly
                if (this->currPawn == NULL) {
                    if (isDown) this->mCamera->move(vec3(0, -0.001, 0));
                    else this->mCamera->setSpeed(vec3(0, 0, 0));
                }
                break;

            case SDLK_SPACE: //debugging stuffs
                //this->mCamera->printDebug();
                this->currPawn->printDebug();
                break;

            case SDLK_ESCAPE:
                sudoku();
                break;

            default: //Unhandled key case
                break;
        }

    }

    void cMain::handleUserMouse(int x, int y, int button, bool isDown) {
        switch (button) {
            case SDL_BUTTON_LEFT:
                break;

            case SDL_BUTTON_RIGHT:
                break;

            case SDL_BUTTON_MIDDLE:
                break;

            case GAME_MOUSE_MOVE:
                /* Rotate the screen in accordance to mouse dx, dy */
                this->mCamera->rotate(-x, vec3(0, 1, 0));
                this->mCamera->rotate(y, vec3(1, 0, 0));
                /* Pawn doesn't ever get rotated */
                break;

            default:
                break;
        }
    }

    void cMain::handleUserScroll(int dx, int dy) { //Only care about the forwards/backwards scroll movement to control the camera (first-person -> third person)
        if (dy < 0) { //Third person
            this->currPawn->setThirdPerson(true);
        }
        else { //First person
            this->currPawn->setThirdPerson(false);
        }
    }

}