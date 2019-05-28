//
// Created by picto on 5/8/2019.
//
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <thread>
#include <mutex>
#include "Board.h"
#include "Player.h"

Player::Player() {
    locationX = 0;
    locationY = 0;
    for(int i = 0; i < 4; i++) {
        directions[i] = 0;
    }
    isMartian = false;
    stillPlaying = true;
    isAlive = true;
}

Player::Player(std::mutex *mtx, Board *board, char initial, int turnNumber) : Player() {
    this->mtx = mtx;
    turnToTake = turnNumber;
    playerBoard = board;
    characterInitial = initial;
    hasCarrot = false;
}

char Player::getCharacterInitial() {
    return characterInitial;
}

void Player::getLocation(int *x, int *y) {
    *x = locationX;
    *y = locationY;
}

bool Player::getHasCarrot() {
    return hasCarrot;
}

void Player::setLocation(int x, int y) {
    this->locationX = x;
    this->locationY = y;
}

void Player::pickDirection() {
    direction = rand() % 4;
    if(directions[direction] != 0) {
        if(direction == 3) {
            direction = 0;
        } else {
            direction++;
        }
    }
    switch(direction) {
        case 0:
            nextX = locationX;
            nextY = locationY + 1;
            break;
        case 1:
            nextX = locationX + 1;
            nextY = locationY;
            break;
        case 2:
            nextX = locationX;
            nextY = locationY - 1;
            break;
        case 3:
            nextX = locationX - 1;
            nextY = locationY;
            break;
    }
}

bool Player::checkOutOfBounds(int nextX, int nextY) {
    if(nextX < 5 && nextY < 5 && nextX > -1 && nextY > -1) {
        return true;
    }
    return false;
}

void Player::setMartian() {
    isMartian = true;
}

bool Player::checkForObject(int nextX, int nextY) {
    bool validMove = false;
    int object = playerBoard->getObjectAtLocation(nextX, nextY);
    switch(object) {
        case 0:
            validMove = true;
            break;
        case 1:
            validMove = true;
            potentialCarrot = true;
            break;
        case 2:
            if(hasCarrot) {
                validMove = true;
            }
            break;
        default:
            return isMartian;
    }
    return validMove;
}

void Player::setCarrot(bool victimHasCarrot) {
    hasCarrot = victimHasCarrot;
}

bool Player::checkMartian() {
    return isMartian;
}

bool Player::getAlive() {
    return isAlive;
}

void Player::setAlive(bool alive) {
    isAlive = alive;
}

void Player::takeTurn() {
    srand(time(NULL));
    while (stillPlaying) {
        if (playerBoard->lastTurnTaken == turnToTake) {
            bool hasMoved = false;
            mtx->lock();
            //_sleep(1000);
            std::cout << characterInitial << " is taking their turn \n";
            if(isAlive) {
                while (!hasMoved) {
                    pickDirection();
                    if (checkOutOfBounds(nextX, nextY)) {
                        if (checkForObject(nextX, nextY)) {
                            hasMoved = playerBoard->updatePosition(locationX, locationY, nextX, nextY);
                            if (hasMoved) {
                                playerBoard->printBoard();
                            }
                        }
                    }
                    if (potentialCarrot && hasMoved) {
                        hasCarrot = true;
                    } else {
                        potentialCarrot = false;
                    }
                    directions[direction] = 1;
                }
                for (int i = 0; i < 4; i++) {
                    directions[i] = 0;
                }
            }
            if (turnToTake == 3) {
                playerBoard->lastTurnTaken = 0;
            }
            else
            {
                playerBoard->lastTurnTaken = turnToTake + 1;
            }
            if(turnToTake == 2) {
                playerBoard->randomMoveMountain();
            }
            std::cout << playerBoard->lastTurnTaken << "\n";
            mtx->unlock();
        }
    }
}
