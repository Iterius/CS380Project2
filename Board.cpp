#include "Board.h"
#include <thread>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "Player.h"
#include <mutex>
#include <iterator>
#include "Martian.h"
int MAX_THREADS = 4;
Board::Board(std::mutex *mtx)
{

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
    for(int x = 0; x < 4; x++)
    {
        if(x == 0)
            initial = 'B';
        else if (x == 1)
            initial = 'D';
        else if (x == 2)
            initial = 'T';
        else if (x == 3)
            initial = 'M';
        if(x == 3)
        {
            players.push_back((Player)*(new Martian(mtx, this, initial)));
        }
        else
        {
            players.push_back(*(new Player(mtx, this, initial)));
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
    int newX, newY;
    findValidPosition(&newX, &newY);
    positions[mountainX][mountainY] = 0;
    positions[newX][newY] = 2;
    mountainX = newX;
    mountainY = newY;
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
    return won;
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
            won = positions[oldx][oldy]-2;
            moveToPosition(toMove, x, y);
            return true;
        }
        else
        {
            return false;
        }
    }
    else if (positions[x][y] > 2)
    {
        if(toMove->isMartian())
        {
            if(toMove->getHasCarrot() && players.at(positions[oldx][oldy]-3).getHasCarrot())
            {
                carrotFlagX = x;
                carrotFlagY = y;
                flagCovered = true;
            }
            else if (players.at(positions[oldx][oldy-3]).getHasCarrot())
            {
                toMove->setCarrot(true);
            }
            std::vector<Player>::iterator itr = players.begin();
            itr += positions[oldx][oldy]-3;
            players.erase(itr);
            int toUpdateX = 0;
            int toUpdateY = 0;
            for(int x = positions[oldx][oldy]-3; x < players.size();x++)
            {
                players.at(x).getLocation(&toUpdateX, &toUpdateY);
                positions[toUpdateX][toUpdateY]--;
            }
            moveToPosition(toMove, x, y);
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
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
        if(positions[x][y] == 1 && toMove->getHasCarrot())
        {
            carrotFlagX = x;
            carrotFlagY = y;
            flagCovered = true;
        }
        return true;
    }
}
