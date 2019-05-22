#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include "Board.h"
using namespace std;
#define NUM_THREADS 5
Player *turnTaker;

void runPlayer() {
    turnTaker->takeTurn();
}

int main()
{
    mutex mutex;
    thread playerThreads[NUM_THREADS];
    Board board = *(new Board(&mutex));
    int win = 0;
    vector<Player> *players = board.getPlayers();
    while(win == 0)
    {
        board.printBoard();
        for(int x = 0; x < players->size(); x++)
        {
            turnTaker = &players->at(x);
            playerThreads[x] = std::thread(runPlayer);
        }
        for(int x = 0; x < players->size(); x++)
        {
            playerThreads[x].join();
        }
        win = board.hasWon();
    }

}
