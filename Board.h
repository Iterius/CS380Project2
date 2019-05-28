#ifndef BOARD_H
#define BOARD_H
#include <math.h>
#include <vector>
#include <mutex>
#include "Player.h"

class Board
{
    public:
        Board(std::mutex *mtx);
        void printBoard();
        ~Board();
        int getObjectAtLocation(int x, int y);
        void moveToPosition(Player *toMove, int x, int y);
        bool updatePosition(int oldx, int oldy, int x, int y);
        int hasWon();
        int lastTurnTaken;
        void removePlayer(int index);
        std::vector<Player>* getPlayers();
        void randomMoveMountain();
        void stopPlaying();

    protected:

    private:
        int positions[5][5];
        int mountainMove;
        int mountainX;
        int mountainY;
        int carrotFlagX;
        int carrotFlagY;
        std::vector<Player> players;
        std::mutex *mtx;
        void findValidPosition(int* x, int *y);
        bool flagCovered;
        bool someoneWon;
        int won;

};

#endif // BOARD_H
