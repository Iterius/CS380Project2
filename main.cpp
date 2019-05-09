#include <iostream>
#include <pthread.h>
#include <vector>
#include "Board.h"
using namespace std;
#define NUM_THREADS 5

int main()
{
    Board board = new Board();
    int win = 0;
    pthread_t threads[NUM_THREADS];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    while(win == 0)
    {
        vector<Player> players = board.getPlayers();
        for(int x = 0; x < players.size(); x++)
        {
            pthread_create(&threads[i], &attr, players.at(x).takeTurn, nullptr);
        }
        for(int x = 0; x < players.size(); x++)
        {
            pthread_join(threads[i], &status);
        }
        win = board.hasWon();
    }
}
