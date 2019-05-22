//
// Created by picto on 5/22/2019.
//

#ifndef CS380PROJECT2_RACER_H
#define CS380PROJECT2_RACER_H

#include <mutex>
#include <vector>
#include "Player.h"

class Race;
class Racer {
private:
    int position;
    std::mutex *mtx;
    Race *race;
public:
    void takeTurn();
};


#endif //CS380PROJECT2_RACER_H
