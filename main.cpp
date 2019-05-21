#include <iostream>
#include <pthread.h>
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
    pthread_mutex_t mutex = new pthread_mutex_t;
    if (pthread_mutex_init(&mutex, NULL) != 0)
    {
        printf("\n mutex init has failed\n");
        return 1;
    }
    Board board = new Board(mutex);
    int win = 0;
    pthread_t threads[NUM_THREADS];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    std::vector<Player> *players = board.getPlayers();
    while(win == 0)
    {
        for(int x = 0; x < players->size(); x++)
        {
            Player* player = &players->at(x);
            pthread_create(&threads[x], &attr, runPlayer, (void*)player);
        }
        for(int x = 0; x < players->size(); x++)
        {
            pthread_join(threads[x], &status);
        }
        win = board.hasWon();
    }

}
