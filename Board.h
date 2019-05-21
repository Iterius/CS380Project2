#ifndef BOARD_H
#define BOARD_H
#include <math.h>
#include <vector>
#include <mutex>
#include "Player.h"

class Board
{
    public:
        Board(std::mutex *mutex);
        void printBoard();
        ~Board();
        int getObjectAtLocation(int x, int y);
        void moveToPosition(Player *toMove, int x, int y);
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
        std::mutex *mutex;
        void findValidPosition(int* x, int *y);
        bool flagCovered;
        int won;

};

#endif // BOARD_H
