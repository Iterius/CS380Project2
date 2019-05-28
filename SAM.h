//
// Created by picto on 5/22/2019.
//

#ifndef CS380PROJECT2_SAM_H
#define CS380PROJECT2_SAM_H

#include <mutex>

class SAM {
private:
    bool hasFired;
    int turnToTake;
    int numPlayers;
    Race *race;
    std::mutex *mtx;
public:
    SAM(std::mutex *mtx, Race *race, int turnNumber, int playerNum);
    void takeShot();
    bool stillPlaying;
};


#endif //CS380PROJECT2_SAM_H
