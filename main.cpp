#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include "Board.h"
#include "Race.h"
#include "Racer.h"
#include "SAM.h"
using namespace std;
#define NUM_THREADS_1 4
#define NUM_THREADS_2 3
void phase2(vector<Player> * players)
{
    cout<<"Starting Phase 2: \n";
    mutex mtx;
    thread racerThreads[NUM_THREADS_2];
    Race *race = (new Race(&mtx, players));
    race->setLastTurnTaken(players->size());
    std::vector<Racer> *racers = race->getRacers();
    int win = 0;
    SAM *sam = new SAM(&mtx, race, racers->size()-1, racers->size());
    race->printRace();
    for(int x = 0; x < racers->size(); x++)
    {
        racerThreads[x] = thread(&Racer::takeTurn, &racers->at(x));
    }
    racerThreads[2] = thread(&SAM::takeShot, sam);
    while(win == 0)
    {
        mtx.lock();
        win = race->hasWon();
        mtx.unlock();
    }
    cout << "GGNORE \n";
    race->stopPlaying();
    sam->stillPlaying = false;
    for(int x = 0; x < racers->size(); x++)
    {
        racerThreads[x].join();
    }
    racerThreads[2].join();
    cout<< racers->at(win-1).getCharacterInitial() << " Has Won!";
}
vector<Player>* phase1()
{
    mutex mtx;
    vector<Player> *winners = new vector<Player>();
    thread playerThreads[NUM_THREADS_1];
    Board *board = (new Board(&mtx));
    int win = 0;
    vector<Player> *players = board->getPlayers();
    int mountainMove = 0;
    board->printBoard();
    for(int x = 0; x < players->size(); x++)
    {
        playerThreads[x] = std::thread(&Player::takeTurn, &players->at(x));
    }
    while(win == 0)
    {
        mtx.lock();
        win = board->hasWon();
        if(win != 0)
        {
            winners->push_back(players->at(win-1));
            bool playersAlive = false;
            for(int i = 0; i < players->size(); i++) {
                if(players->at(i).getAlive()) {
                    playersAlive = true;
                }
            }
            if(playersAlive && winners->size() < 2)
            {
                cout << winners->size() << " size of player when player got out. \n";
                win = 0;
            }
            else
            {
                cout << "made it to stop playing";
                board->stopPlaying();
            }
        }
        mtx.unlock();
    }
    for(int x = 0; x < players->size(); x++)
    {
        playerThreads[x].join();
    }
    return winners;
}

int main()
{
    std::vector<Player> *winners = phase1();
    cout<<"Finished phase 1: \n";
    phase2(winners);

}

