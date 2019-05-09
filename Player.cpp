//
// Created by picto on 5/8/2019.
//

#include <stdlib.h>
#include <time.h>
#include "Board.h"
#include "Player.h"

Player::Player() {
    locationX = 0;
    locationY = 0;
}
Player::Player(int locationX, int locationY) {
    this->locationX = locationX;
    this->locationY = locationY;
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

}
bool Player::checkForObject(int nextX, int nextY) {

}
void Player::takeTurn() {
    int nextPosition;
    bool hasMoved = false;
    while(!hasMoved) {
        pickDirection();
        checkOutOfBounds(nextX, nextY);
        checkForObject(nextX, nextY);
        hasMoved = updatePositon(nextPosition, locationX, locationY);
    }
}