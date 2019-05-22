//
// Created by picto on 5/22/2019.
//

#include "Race.h"
#include "Racer.h"

Racer::Racer() {
    position = 0;
}

Racer::Racer(std::mutex *mtx, Race *race, char initial) {
    this->mtx = mtx;
    this->race = race;
    characterInitial = initial;
}

int Racer::getPosition() {
    return position;
}

void Racer::takeTurn() {
    mtx->lock();
    if (!race.isFrozen(racerNumber)) {
        position = position + 1;
    } else {
        race.toggleFrozen(racerNumber);
    }
    mtx->unlock();
}