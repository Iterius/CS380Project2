//
// Created by picto on 5/22/2019.
//

#include "Race.h"
#include "Racer.h"

Racer::Racer(std::mutex *mtx, Race *race, char initial, int turnNumber) {
    position = 0;
    turnToTake =  turnNumber;
    stillPlaying = true;
    this->mtx = mtx;
    this->race = race;
    characterInitial = initial;
}

int Racer::getPosition() {
    return position;
}

char Racer::getCharacterInitial() {
    return characterInitial;
}

void Racer::takeTurn() {
    while (stillPlaying) {
        if (race->lastTurnTaken == turnToTake) {
            mtx->lock();
            if (!race->isFrozen(racerNumber)) {
                position = position + 1;
            } else {
                race->toggleFrozen(racerNumber);
            }
            mtx->unlock();
            if(race->lastTurnTaken == 0) {
                race->lastTurnTaken = turnToTake + 1;
            }
            else
            {
                race->lastTurnTaken = 0;
            }
        }
    }
}