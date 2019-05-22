//
// Created by picto on 5/22/2019.
//

#include <mutex>
#include <vector>
#include "Race.h"
#include "Player.h"
#include "Racer.h"

Race::Race(std::mutex *mtx, std::vector<Player> *players) {
    won = 0;
    length = 10;
    this.mtx = mtx;
    std::vector<Racer> * temp();
    for(int x = 0; x < players->size(); x++)
    {
        temp.pushback(Racer(mtx, this, players->at(x).getCharacterInitial()));
    }
    racers = temp;
};

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
    position1 = racers->at(1).getPosition;
    position2 = racers->at(2).getPosition;
    for(int x = 0; x < length; x++)
    {
        if(position1 == x)
        {
            cout<< racers->at(1).getCharacterInitial() << "     ";
        }
        else
        {
            cout<< "-     ";
        }
        if(position2 == x)
        {
            cout << racers->at(2).getCharacterInitial() << "     ";

        }
        else
        {
            cout<<"-     ";
        }
    }
}
int Race::hasWon()
{
    for(int x = 0; x < racers->size(); x++)
    {
        if(racers->at(x).getPosition >= length)
        {
            won = x+1;
        }
    }
    return won;
}
