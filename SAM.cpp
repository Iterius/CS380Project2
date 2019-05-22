//
// Created by picto on 5/22/2019.
//

#include "Race.h"
#include "SAM.h"

SAM::SAM(std::mutex *mtx, Race *race) {
    hasFired = false;
    this->mtx = mtx;
    this->race = race;
}

void SAM::takeShot() {
    if(!hasFired) {
        srand(time(NULL));
        int target = rand() % 2;
        int hitTarget = rand() % 2;
        if(hitTarget == 1) {
            mtx->lock();
            race->setFrozen(target, true);
            mtx->unlock();
        }
        hasFired = true;
    } else {
        hasFired = false;
    }
}