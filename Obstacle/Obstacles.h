//
// Created by adlarkin on 1/11/19.
//

#ifndef RRT_STAR_CPP_OBSTACLES_H
#define RRT_STAR_CPP_OBSTACLES_H


#include <cstddef>
#include <vector>
#include "DisplayableRectObstacle.h"

class Obstacles {
public:
    Obstacles(size_t scaledPointRange, size_t numOfObstacles);
    const std::vector<DisplayableRectObstacle> &getExistingObstacles() const;

private:
    void generateObstacles(size_t scaledPointRange, size_t numOfObstacles);
    DisplayableRectObstacle makeRandomObstacle(size_t scaledPointRange);

    std::vector<DisplayableRectObstacle> existingObstacles;
};


#endif //RRT_STAR_CPP_OBSTACLES_H
