//
// Created by picto on 5/22/2019.
//

#include "Race.h"
#include "SAM.h"

SAM::SAM(std::mutex *mtx) {
    hasFired = false;
    this->mtx = mtx;
}

void SAM::takeShot() {
    if(!hasFired) {
        srand(time(NULL));
        int target = rand() % 2;
        int hitTarget = rand() % 2;
        if(hitTarget == 1) {
            if(target == 0) {
                mtx->lock();
                Race::setFrozen(target);
                mtx->unlock();
            } else {
                mtx->lock();
                Race::setFrozen(target);
                mtx->unlock();
            }
        }
        hasFired = true;
    } else {
        hasFired = false;
    }
}