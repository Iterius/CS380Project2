//
// Created by picto on 5/8/2019.
//

#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include "Board.h"
#include "Player.h"

Player::Player() {
    locationX = 0;
    locationY = 0;
}

Player::Player(pthread_mutex_t *mutex, Board *board, char initial) : Player() {
    this->mutex = mutex;
    playerBoard = board;
    characterInitial = initial;
}

char Player::getCharacterInitial() {
    return characterInitial;
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
    if(nextX > 4 || nextY > 4 || nextX < 0 || nextY < 0) {

    }
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
        case default
    }
}

void Player::takeTurn() {
    int nextPosition;
    bool hasMoved = false;
    while(!hasMoved) {
        pickDirection();
        checkOutOfBounds(nextX, nextY);
        checkForObject(nextX, nextY);
        int pthread_mutex_lock(pthread_mutex_t *mutex);
        hasMoved = playerBoard->updatePosition(/*locationx, locationy, nextx, nexty*/);
        int pthread_mutex_unlock(pthread_mutex_t *mutex);
        if(potentialCarrot && hasMoved) {
            hasCarrot = true;
        } else {
            potentialCarrot = false;
        }
    }
}