#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include "Board.h"
using namespace std;
#define NUM_THREADS 5

void* runPlayer(void* player) {
    Player* turnTaker = (Player*) player;
    turnTaker->takeTurn();
}

int main()
{
    mutex mutex;
    thread playerThreads[NUM_THREADS];
    Board board = new Board(mutex);
    int win = 0;
    std::vector<Player> *players = board.getPlayers();
    while(win == 0)
    {
        for(int x = 0; x < players->size(); x++)
        {
            Player* player = &players->at(x);
            playerThreads[x] = threadObj(player->takeTurn());
        }
        for(int x = 0; x < players->size(); x++)
        {
            playerThreads[x].join();
        }
        win = board.hasWon();
    }

}
