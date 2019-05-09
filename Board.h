#ifndef BOARD_H
#define BOARD_H
#include <math.h>

class Board
{
    public:

        Board();
        void printBoard();
        ~Board();
        int getObjectAtLocation(int x, int y);
        bool updatePosition(int id, int x, int y);
        int hasWon();
        vector<Player> getPlayers();

    protected:

    private:
        int[][] positions;
        int mountainX;
        int mountainY;
        int carrotFlagX;
        int carrotFlagY;
        vector<Player> players;
};

#endif // BOARD_H
