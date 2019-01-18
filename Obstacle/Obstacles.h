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
    bool isObstacleFree(const Location& location) const;

private:
    void generateObstacles(size_t scaledPointRange, size_t numOfObstacles);
    DisplayableRectObstacle makeRandomObstacle(size_t scaledPointRange, size_t maxDimension, size_t minDimension,
            bool shorterWidth, bool shorterHeight);

    std::vector<DisplayableRectObstacle> existingObstacles;
};


#endif //RRT_STAR_CPP_OBSTACLES_H
