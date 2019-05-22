//
// Created by picto on 5/22/2019.
//

#ifndef CS380PROJECT2_SAM_H
#define CS380PROJECT2_SAM_H

#include <mutex>

class SAM {
private:
    std::mutex *mtx;
public:
    SAM();
    SAM(std::mutex *mtx);
    void takeShot();
};


#endif //CS380PROJECT2_SAM_H
