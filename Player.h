//
// Created by picto on 5/8/2019.
//

#ifndef CS380PROJECT2_PLAYER_H
#define CS380PROJECT2_PLAYER_H


class Player {
private:
    int locationX;
    int locationY;
    int nextX;
    int nextY;
    void pickDirection();
    bool checkOutOfBounds(int nextX, int nextY);
    bool checkForObject(int nextX, int nextY);
public:
    Player();
    Player(int locationX, int locationY);
    void takeTurn();
};

#endif //CS380PROJECT2_PLAYER_H
/* Call take turn, take turn calls move, take turn calls checkoutofbounds, take turn calls checkforobject, */