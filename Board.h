#ifndef BOARD_H
#define BOARD_H
#include <math.h>
#include <vector>
#include "Player.h"

class Board
{
    public:
        Board(pthread_mutex_t mutex);
        void printBoard();
        ~Board();
        int getObjectAtLocation(int x, int y);
        bool updatePosition(int oldx, int oldy, int x, int y);
        int hasWon();
        std::vector<Player>* getPlayers();
        void randomMoveMountain();

    protected:

    private:
        int positions[5][5];
        int mountainX;
        int mountainY;
        int carrotFlagX;
        int carrotFlagY;
        std::vector<Player> players;
        pthread_mutex_t mutex;
        void findValidPosition(int* x, int *y);
        bool flagCovered;
        int won;

};

#endif // BOARD_H
