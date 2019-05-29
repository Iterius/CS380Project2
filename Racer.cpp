//
// Created by picto on 5/22/2019.
//

#include "Race.h"
#include "Racer.h"
#include <iostream>

Racer::Racer(std::mutex *mtx, Race *race, char initial, int turnNumber) {
    position = 0;
    if(turnNumber == 0) {
        racerNumber = 2;
    } else {
        racerNumber = 1;
    }
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
        if (race->getLastTurnTaken() == turnToTake && race->hasWon() == 0) {
            mtx->lock();
            std::cout << characterInitial << " is taking his turn. \n";
            if (!race->isFrozen(racerNumber)) {
                position = position + 1;
            } else {
                race->toggleFrozen(racerNumber);
            }
            race->printRace();
            if(race->getLastTurnTaken() == 0) {
                race->setLastTurnTaken(turnToTake + 1);
            }
            else
            {
                race->setLastTurnTaken(0);
            }
            mtx->unlock();
        }
    }
}