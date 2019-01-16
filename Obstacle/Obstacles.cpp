//
// Created by adlarkin on 1/11/19.
//

#include "Obstacles.h"

#define OBSTACLE_SPACE 0.75  // obstacles should only take up no more than this much of the search space

Obstacles::Obstacles(size_t scaledPointRange, size_t numOfObstacles) {
    generateObstacles(scaledPointRange, numOfObstacles);
}

const std::vector<DisplayableRectObstacle> &Obstacles::getExistingObstacles() const {
    return existingObstacles;
}

bool Obstacles::isObstacleFree(const Location &location) const {
    for (auto ob : existingObstacles) {
        if (ob.isInX(location) && ob.isInY(location)) {
            return false;
        }
    }
    return true;
}

void Obstacles::generateObstacles(size_t scaledPointRange, size_t numOfObstacles) {
    // set the max length and width of the rectangular obstacles
    // this is so that the combined obstacle area doesn't exceed OBSTACLE_SPACE
    auto lengthWidth = (size_t)(OBSTACLE_SPACE * scaledPointRange);
    lengthWidth = lengthWidth / numOfObstacles;

    for (size_t i = 0; i < numOfObstacles; ++i) {
        DisplayableRectObstacle nextOb = makeRandomObstacle(scaledPointRange, lengthWidth);
        existingObstacles.push_back(nextOb);
    }
}

DisplayableRectObstacle Obstacles::makeRandomObstacle(size_t scaledPointRange, size_t maxDimension) {
    DisplayableRectObstacle obstacle(scaledPointRange, maxDimension);

    // make sure the newly created obstacle doesn't overlap with other obstacles
    bool overlaps = true;
    while (overlaps) {
        overlaps = false;
        for (auto obs : existingObstacles) {
            if (obs.obstaclesOverlap(obstacle)) {
                obstacle = DisplayableRectObstacle(scaledPointRange, maxDimension);
                overlaps = true;
            }
        }
    }

    return obstacle;
}
