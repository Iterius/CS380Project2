//
// Created by picto on 5/8/2019.
//

#ifndef CS380PROJECT2_MARTIAN_H
#define CS380PROJECT2_MARTIAN_H

#include <thread>
#include <mutex>
#include "Player.h"

class Martian : public Player {
private:

public:
    Martian();
    Martian(std::mutex *mtx, Board *board, char initial);
    bool checkForObject(int nextX, int nextY);
    bool isMartian();
};


#endif //CS380PROJECT2_MARTIAN_H
