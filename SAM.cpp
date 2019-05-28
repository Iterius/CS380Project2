//
// Created by picto on 5/22/2019.
//

#include "Race.h"
#include "SAM.h"

SAM::SAM(std::mutex *mtx, Race *race, int turnNumber, int playerNum) {
    hasFired = false;
    numPlayers = playerNum;
    stillPlaying = true;
    turnToTake = turnNumber;
    this->mtx = mtx;
    this->race = race;
}

void SAM::takeShot() {
    while(stillPlaying) {
        if(race->lastTurnTaken == turnToTake) {
            if (!hasFired) {
                srand(time(NULL));
                int target = rand() % numPlayers;
                int hitTarget = rand() % 2;
                if (hitTarget == 1) {
                    mtx->lock();
                    race->setFrozen(target, true);
                    mtx->unlock();
                }
                hasFired = true;
            } else {
                hasFired = false;
            }
            race->lastTurnTaken = turnToTake + 1;
        }
    }
}