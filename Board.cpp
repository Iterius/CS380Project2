#include "Board.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
Board::Board(pthread_mutex_t mutex)
{
    srand(time(0));
    this.mutex = mutex;
    positions = int[5][5];
    for(int x = 0; x < 5; x++)
    {
        for(int y = 0; y < 5; y++)
        {
            positions[x][y] = 0;
        }
    }
    players = new std::vector<Player>();
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
        players.push_back(new Player(mutex, this, initial));

        int playerX = 0;
        int playerY = 0;
        findValidPosition(*playerX, *playerY);
        players.at(x).setLocation(playerX, playerY);
        positions[playerX][playerY] = x+2;

    }
    findValidPosition(*mountainX, *mountainY);
    positions[mountainX][mountainY] = 2;
    findValidPosition(*carrotFlagX, carrotFlagY);
    positions[carrotFlagX][carrotFlagY] = 1;
    findValidPosition(*carrotFlagX, carrotFlagY);
    positions[carrotFlagX][carrotFlagY] = 1;
    carrotFlagX = 6;
    carrotFlagY = 6;
    flagCovered = false;
}
void Board::findValidPosition(int*x, int*y)
{
    bool found = false;
    srand(time(0));
    while(!found)
    {
        &x = rand() % 5;
        &y = rand() % 5;
        if(positions[x][y] == 0)
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
    cout << endl;
    for(int y = 0; y < 5; y++)
    {
        for(int x = 0;x < 5; x++)
        {
            if(positions[x][y] == 0)
            {
                cout <<"-      ";
            }
            else if(positions[x][y] == 1)
            {
                cout <<"C      ";
            }
            else if(position[x][y] == 2)
            {
                cout <<"M      ";
            }
            else
            {
                char toPrint = players.at(position[x][y] -3 ).getCharacterInitial();
                if(players.at(position[x][y]-3).getHasCarrot())
                {
                    cout<< toPrint << "(C)   ";
                }
                else
                {
                    cout << toPrint <<"      ";
                }
            }
        }
        cout << endl;
    }
}
int getObjectAtLocation(int x, int y)
{
    return positions[x][y];
}
bool Board::updatePosition(int oldx, int oldy, int x, int y)
{
    Player *toMove = *players.at(positions[oldx][oldy]-2);
    if(positions[x][y] == 2)
    {
        if(toMove->getHasCarrot())
        {
            won = positions[oldx][oldy]-1;
            moveToPosition(toMove, x, y);
        }
    }
    else if (positions[x][y] > 2)
    {
        if(toMove->isMartian())
        {
            players.remove(positions[oldx][oldy]-2);
            int toUpdateX = 0;
            int toUpdateY = 0;
            for(int x = 0; x <  )
        }
    }
    else
    {
        if(flagCovered && carrotFlagX == oldx && carrotFlagy == oldy)
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
        toMove->setLocation();
    }
}
