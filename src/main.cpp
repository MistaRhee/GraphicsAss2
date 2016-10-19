#include <cstdio>
#include <cstdlib>

#include "game.h"

int main(int argc, char** argv) {
    __game__::cMain mGame(argc, argv);
    try {
        mGame.run();
    }
    catch (...) {
        //Nothing ATM
    }
    return EXIT_SUCCESS;
}