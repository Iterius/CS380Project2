//
// Created by picto on 5/8/2019.
//

#ifndef CS380PROJECT2_PLAYER_H
#define CS380PROJECT2_PLAYER_H

#include <thread>
#include <mutex>
class Board;
class Player {
protected:
    int locationX;
    int locationY;
    int nextX;
    int nextY;
    char characterInitial;
    Board *playerBoard;
    std::mutex *mutex;
    bool potentialCarrot;
    bool hasCarrot;
    void pickDirection();
    bool checkOutOfBounds(int nextX, int nextY);
    bool checkForObject(int nextX, int nextY);
public:
    Player();
    Player(std::mutex *mutex, Board *board, char initial);
    char getCharacterInitial();
    void getLocation(int *x, int *y);
    bool getHasCarrot();
    bool isMartian();
    void setCarrot(bool victimHasCarrot);
    void setLocation(int x, int y);
    void takeTurn();
};

#endif //CS380PROJECT2_PLAYER_H
/* Call take turn, take turn calls move, take turn calls checkoutofbounds, take turn calls checkforobject, */
