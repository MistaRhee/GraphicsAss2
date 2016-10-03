#include <cstdio>
#include <cstdlib>

#include "game.h"

int main(int argc, char** argv) {
    __game__::cMain mGame(argc, argv);
    mGame.run();
    return EXIT_SUCCESS;
}