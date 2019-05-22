//
// Created by picto on 5/8/2019.
//

#include <stdlib.h>
#include <time.h>
#include <thread>
#include <mutex>
#include "Board.h"
#include "Player.h"

Player::Player() {
    locationX = 0;
    locationY = 0;
}

Player::Player(std::mutex *mutex, Board *board, char initial) : Player() {
    this->mutex = mutex;
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
    srand(time(NULL));
    int direction = rand() % 4;
    switch(direction) {
        case '0':
            nextX = locationX;
            nextY = locationY + 1;
            break;
        case '1':
            nextX = locationX + 1;
            nextY = locationY;
            break;
        case '2':
            nextX = locationX;
            nextY = locationY - 1;
            break;
        case '3':
            nextX = locationX - 1;
            nextY = locationY;
            break;
    }
}

bool Player::checkOutOfBounds(int nextX, int nextY) {
    if(nextX < 4 && nextY < 4 && nextX > 0 && nextY > 0) {
        return true;
    }
    return false;
}

bool Player::checkForObject(int nextX, int nextY) {
    bool validMove = false;
    int object = playerBoard->getObjectAtLocation(nextX, nextY);
    switch(object) {
        case '0':
            validMove = true;
            break;
        case '1':
            validMove = true;
            potentialCarrot = true;
            break;
        case '2':
            if(hasCarrot) {
                validMove = true;
            }
            break;
        default:
            break;
    }
    return validMove;
}

void Player::setCarrot(bool victimHasCarrot) {
    hasCarrot = victimHasCarrot;
}

bool Player::isMartian() {
    return false;
}

void Player::takeTurn() {
    bool hasMoved = false;
    while(!hasMoved) {
        pickDirection();
        if(checkOutOfBounds(nextX, nextY)) {
            if (checkForObject(nextX, nextY)){
                mutex->lock();
                hasMoved = playerBoard->updatePosition(locationX, locationY, nextX, nextY);
                mutex->unlock();
            }
        }
        if(potentialCarrot && hasMoved) {
            hasCarrot = true;
        } else {
            potentialCarrot = false;
        }
    }
}
