//
// Created by picto on 5/8/2019.
//

#include "Player.h"
#include "Martian.h"
#include "Board.h"
#include <thread>
#include <mutex>


Martian::Martian(std::mutex *mutex, Board *board, char initial) : Player(){
    this->mutex = mutex;
    playerBoard = board;
    characterInitial = initial;
}

bool Martian::checkForObject(int nextX, int nextY) {
    bool validMove = false;
    int object = playerBoard->getObjectAtLocation(nextX, nextY);
    switch(object) {
        case '0':
            validMove = true;
            break;
        case '1':
            validMove = true;
            Martian::potentialCarrot = true;
            break;
        case '2':
            if(hasCarrot) {
                validMove = true;
            }
            break;
        default:
            validMove = true;
            break;
    }
    return validMove;
}

bool Martian::isMartian() {
    return true;
}