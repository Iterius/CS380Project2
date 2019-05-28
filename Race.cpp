//
// Created by picto on 5/22/2019.
//

#include <mutex>
#include <vector>
#include <iostream>
#include "Race.h"
#include "Player.h"
#include "Racer.h"
using namespace std;

Race::Race(std::mutex *mtx, std::vector<Player> *players) {
    won = 0;
    length = 10;
    int lastTurnTaken = players->size();
    player1Frozen = false;
    player2Frozen = false;
    int turnNumber;
    this->mtx = mtx;
    if(players->size() == 1 )
    {
        oneRacer = true;
    }
    else
    {
        oneRacer = false;
    }
    racers = new std::vector<Racer>();
    for(int x = 0; x < players->size(); x++)
    {
        if (x == 0) {
            turnNumber = players->size()+1;
        }
        else
        {
            turnNumber = (x-1);
        }
        racers->push_back(*(new Racer(mtx, this, players->at(x).getCharacterInitial(), turnNumber)));
    }
}

bool Race::isFrozen(int racer)
{
    if(racer == 0)
    {
        return player1Frozen;
    }
    else
    {
        return player2Frozen;
    }
}
void Race::toggleFrozen(int racer)
{
    if (racer == 0)
    {
        player1Frozen = !player1Frozen;
    }
    else
    {
        player2Frozen = !player2Frozen;
    }
}
std::vector<Racer> *Race::getRacers() {
    return racers;
}
void Race::setFrozen(int racer, bool frozen)
{
    if(racer == 0)
    {
        player1Frozen = frozen;
    }
    else
    {
        player2Frozen = frozen;
    }
}
void Race::printRace()
{
    int position1 = racers->at(0).getPosition();
    for(int x = 0; x < length; x++)
    {
        if(position1 == x)
        {
            cout<< racers->at(0).getCharacterInitial() << "     ";
        }
        else
        {
            cout<< "-     ";
        }
        if(!oneRacer)
        {
            int position2 = racers->at(1).getPosition();
            if(position2 == x)
            {
                cout << racers->at(1).getCharacterInitial() << "     ";

            }
            else
            {
                cout<<"-     ";
            }
        }
        cout<<"\n";
    }
    cout<<"===================================================================== \n";
}
int Race::hasWon()
{
    for(int x = 0; x < racers->size(); x++)
    {
        if(racers->at(x).getPosition() >= length)
        {
            won = x+1;
        }
    }
    return won;
}

void Race::stopPlaying() {
    for(int x = 0; x < racers->size(); x++) {
        racers->at(x).stillPlaying = false;
    }
}