//
// Created by picto on 5/22/2019.
//

#ifndef CS380PROJECT2_RACE_H
#define CS380PROJECT2_RACE_H

#include <mutex>
#include <vector>
#include "Player.h"
#include "Racer.h"

class Race {
private:
    std::mutex *mtx;
    bool player1Frozen;
    bool player2Frozen;
    std::vector<Racer> racers;
    int won;

public:
    Race(std::mutex *mtx, std::vector<Player> *players);
    void printRace();
    int hasWon();
};


#endif //CS380PROJECT2_RACE_H
