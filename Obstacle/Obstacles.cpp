//
// Created by adlarkin on 1/11/19.
//

#include "Obstacles.h"

#define OBSTACLE_SPACE 0.5  // obstacles should only take up half of the search space

Obstacles::Obstacles(size_t scaledPointRange, size_t numOfObstacles) {
    generateObstacles(scaledPointRange, numOfObstacles);
}

const std::vector<DisplayableRectObstacle> &Obstacles::getExistingObstacles() const {
    return existingObstacles;
}

void Obstacles::generateObstacles(size_t scaledPointRange, size_t numOfObstacles) {
    for (size_t i = 0; i < numOfObstacles; ++i) {
        DisplayableRectObstacle nextOb = makeRandomObstacle(scaledPointRange);
        existingObstacles.push_back(nextOb);
    }
}

DisplayableRectObstacle Obstacles::makeRandomObstacle(size_t scaledPointRange) {
    DisplayableRectObstacle obstacle(scaledPointRange);
    // todo: do some validity checking here (for when making more than one obstacle)
    return obstacle;
}
