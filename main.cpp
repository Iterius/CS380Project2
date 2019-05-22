#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include "Board.h"
using namespace std;
#define NUM_THREADS 4

int main()
{
    mutex mtx;
    thread playerThreads[NUM_THREADS];
    Board *board = (new Board(&mtx));
    int win = 0;
    vector<Player> *players = board->getPlayers();
    int mountainMove = 0;
    while(win == 0)
    {
        board->printBoard();
        for(int x = 0; x < players->size(); x++)
        {
            playerThreads[x] = std::thread(&Player::takeTurn, &players->at(x));
        }
        for(int x = 0; x < players->size(); x++)
        {
            playerThreads[x].join();
        }
        win = board->hasWon();
        mountainMove++;
        if(mountainMove == 3)
        {
            mountainMove = 0;
            board->randomMoveMountain();
        }
    }
    cout<<players->at(win-1).getCharacterInitial()<<" has won the game thank you jesus someone did it holy hell.";

}
