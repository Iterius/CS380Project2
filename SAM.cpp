//
// Created by picto on 5/22/2019.
//

#include "Race.h"
#include "SAM.h"
#include <random>

SAM::SAM(std::mutex *mtx, Race *race, int turnNumber, int playerNum) {
    hasFired = false;
    numPlayers = playerNum;
    stillPlaying = true;
    turnToTake = turnNumber;
    this->mtx = mtx;
    this->race = race;
}

void SAM::takeShot() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(1, 2);
    while(stillPlaying) {
        if(race->getLastTurnTaken() == turnToTake) {
            mtx->lock();
            if (!hasFired) {
                int target = dist(mt);
                int hitTarget = 1;
                if (hitTarget == 1) {
                    race->setFrozen(target, true);
                }
                hasFired = true;
            } else {
                hasFired = false;
            }
            race->setLastTurnTaken(turnToTake + 1);
            race->printStatus();
            mtx->unlock();
        }
    }
}