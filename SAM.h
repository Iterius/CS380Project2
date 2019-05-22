//
// Created by picto on 5/22/2019.
//

#ifndef CS380PROJECT2_SAM_H
#define CS380PROJECT2_SAM_H

#include <mutex>

class SAM {
private:
    bool hasFired;
    Race *race;
    std::mutex *mtx;
public:
    SAM(std::mutex *mtx, Race *race);
    void takeShot();
};


#endif //CS380PROJECT2_SAM_H
