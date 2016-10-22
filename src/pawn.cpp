#include "pawn.h"

namespace __game__ {

    cPawn::cPawn() {
        this->mCamera = NULL;
        hack();
    }

    cPawn::~cPawn() {} //Not gonna destroy camera in here because nature of detachable camera

}