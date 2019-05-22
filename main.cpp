#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include "Board.h"
using namespace std;
#define NUM_THREADS 4
void phase2(vector<Player> * players)
{

}
vector<Player>* phase1()
{
    mutex mtx;
    vector<Player> *winners = new vector<Player>();
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
        for(int x = 0; x < players->size(); x++)
        {
            if(!players->at(x).getAlive()) {
                board->removePlayer(x);
            }
        }
        win = board->hasWon();
        mountainMove++;
        if(mountainMove == 3)
        {
            mountainMove = 0;
            board->randomMoveMountain();
        }
        if(win != 0)
        {
            winners->push_back(players->at(win+1));
            if(players->size() > 1 && winners->size() < 2)
            {
                win = 0;
            }
        }
    }
    return winners;
}

int main()
{
    phase2(phase1());

}

