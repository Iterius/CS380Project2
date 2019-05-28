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
    std::vector<Racer> *racers;
    int won;
    int length;
    bool oneRacer;

public:
    Race(std::mutex *mtx, std::vector<Player> *players);
    void printRace();
    int hasWon();
    int lastTurnTaken;
    std::vector<Racer> *getRacers();
    bool isFrozen(int racer);
    void toggleFrozen(int racer);
    void setFrozen(int racer, bool frozen);
    void stopPlaying();
};


#endif //CS380PROJECT2_RACE_H
