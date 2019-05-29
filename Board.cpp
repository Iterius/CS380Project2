#include "Board.h"
#include <thread>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "Player.h"
#include <mutex>
#include <iterator>
int MAX_THREADS = 4;
Board::Board(std::mutex *mtx)
{
    lastTurnTaken = 3;
    mountainMove = 0;
    someoneWon = false;
    won = 0;
    srand(time(0));
    this->mtx = mtx;
    for(int x = 0; x < 5; x++)
    {
        for(int y = 0; y < 5; y++)
        {
            positions[x][y] = 0;
        }
    }
    char initial;
    int turnNumber;
    for(int x = 0; x < 4; x++)
    {
        if(x == 0)
        {
            turnNumber = 3;
        }
        else
        {
            turnNumber = (x - 1);
        }
        if(x == 0)
            initial = 'B';
        else if (x == 1)
            initial = 'D';
        else if (x == 2)
            initial = 'T';
        else if (x == 3) {
            initial = 'M';
        }
        players.push_back(*(new Player(mtx, this, initial, turnNumber)));
        if(x == 3) {
            players.at(3).setMartian();
        }
        int playerX = 0;
        int playerY = 0;
        findValidPosition(&playerX, &playerY);
        players.at(x).setLocation(playerX, playerY);
        positions[playerX][playerY] = x+3;

    }
    findValidPosition(&mountainX, &mountainY);
    positions[mountainX][mountainY] = 2;
    findValidPosition(&carrotFlagX, &carrotFlagY);
    positions[carrotFlagX][carrotFlagY] = 1;
    findValidPosition(&carrotFlagX, &carrotFlagY);
    positions[carrotFlagX][carrotFlagY] = 1;
    carrotFlagX = 6;
    carrotFlagY = 6;
    flagCovered = false;
}
void Board::randomMoveMountain()
{
    if(mountainMove == 2) {
        int newX, newY;
        findValidPosition(&newX, &newY);
        positions[mountainX][mountainY] = 0;
        positions[newX][newY] = 2;
        mountainX = newX;
        mountainY = newY;
        mountainMove = 0;
    }
    else
    {
        mountainMove++;
    }
}
void Board::findValidPosition(int*x, int*y)
{
    bool found = false;
    srand(time(0));
    while(!found)
    {
        *x = rand() % 5;
        *y = rand() % 5;
        if(positions[*x][*y] == 0)
        {
            found = true;
        }
    }
}
Board::~Board()
{
    //dtor
}

void Board::printBoard()
{
    std::cout << std::endl;
    for(int y = 0; y < 5; y++)
    {
        for(int x = 0;x < 5; x++)
        {
            if(positions[x][y] == 0)
            {
                std::cout <<"-      ";
            }
            else if(positions[x][y] == 1)
            {
                std::cout <<"C      ";
            }
            else if(positions[x][y] == 2)
            {
                std::cout <<"F      ";
            }
            else
            {
                char toPrint = players.at(positions[x][y] -3 ).getCharacterInitial();
                if(players.at(positions[x][y]-3).getHasCarrot())
                {
                    std::cout<< toPrint << "(C)   ";
                }
                else
                {
                    std::cout << toPrint <<"      ";
                }
            }
        }
        std::cout << std::endl;
    }
}
int Board::getObjectAtLocation(int x, int y)
{
    return positions[x][y];
}
std::vector<Player>* Board::getPlayers()
{
    return &players;
}
int Board::hasWon()
{
    int toReturn = won;
    won = 0;
    return toReturn;
}
void Board::moveToPosition(Player *toMove, int x, int y)
{
    int previousX = 6;
    int previousY = 6;
    toMove->getLocation(&previousX, &previousY);
    positions[x][y] = positions[previousX][previousY];
    toMove->setLocation(x,y);
    positions[previousX][previousY] = 0;

}
bool Board::updatePosition(int oldx, int oldy, int x, int y)
{
    Player *toMove = &players.at(positions[oldx][oldy]-3);
    if(positions[x][y] == 2)
    {
        if(toMove->getHasCarrot())
        {
            removePlayer(positions[oldx][oldy]-3);
            won = positions[oldx][oldy]-2;
            positions[oldx][oldy] = 0;
            if(someoneWon) {
                for(int i = 0; i < players.size(); i++) {
                    removePlayer(i);
                }
            } else {
                someoneWon = true;
            }
            return true;
        }
        else
        {
            return false;
        }
    }
    else if (positions[x][y] > 2)
    {
        if(toMove->checkMartian())
        {
            if(toMove->getHasCarrot() && players.at(positions[x][y]-3).getHasCarrot())
            {
                carrotFlagX = x;
                carrotFlagY = y;
                flagCovered = true;
            }
            else if (players.at(positions[x][y]-3).getHasCarrot())
            {
                toMove->setCarrot(true);
            }
            players.at(positions[x][y]-3).setAlive(false);
            moveToPosition(toMove, x, y);
            if(flagCovered && carrotFlagX == oldx && carrotFlagY == oldy)
            {
                std::cout << "Marvin killed some dude with a carrot";
                positions[oldx][oldy] = 1;
                carrotFlagX = 6;
                carrotFlagY = 6;
                flagCovered = false;
            }
            else
            {
                positions[oldx][oldy] = 0;
            }
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        if(positions[x][y] == 1 && toMove->getHasCarrot())
        {
            carrotFlagX = x;
            carrotFlagY = y;
            flagCovered = true;
        }
        moveToPosition(toMove, x, y);
        if(flagCovered && carrotFlagX == oldx && carrotFlagY == oldy)
        {
            positions[oldx][oldy] = 1;
            carrotFlagX = 6;
            carrotFlagY = 6;
            flagCovered = false;
        }
        else
        {
            positions[oldx][oldy] = 0;
        }
        return true;
    }
}
void Board::removePlayer(int index) {
    players.at(index).setAlive(false);
}
void Board::stopPlaying() {
    for(int x = 0; x < players.size(); x++) {
        players[x].stillPlaying = false;
    }
}
