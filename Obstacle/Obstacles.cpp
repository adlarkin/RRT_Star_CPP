//
// Created by adlarkin on 1/11/19.
//

#include <iostream>
#include "Obstacles.h"
#include <math.h>

#define MAX_OB_SPACE 0.35   // obstacles should take up no more than this much of the search space
#define MIN_OB_SPACE 0.25   // obstacles should take up no less than this much of the search space

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
    // set the max/min length and width of the rectangular obstacles
    // this is so that there's a good ratio between the total space and obstacle space
    size_t totalArea = scaledPointRange * scaledPointRange;
    auto maxLengthWidth = (size_t) sqrt((MAX_OB_SPACE * totalArea) / numOfObstacles);
    auto minLengthWidth = (size_t) sqrt((MIN_OB_SPACE * totalArea) / numOfObstacles);

    // for every obstacle that's made, 'transpose' it (so there are differently oriented obstacles)
    bool shorterWidth = false;
    bool shorterHeight = true;
    for (size_t i = 0; i < numOfObstacles; ++i) {
        DisplayableRectObstacle nextOb = makeRandomObstacle(scaledPointRange, maxLengthWidth, minLengthWidth,
                shorterWidth, shorterHeight);
        existingObstacles.push_back(nextOb);
        // changing the orientation of the next obstacle
        shorterWidth = !shorterWidth;
        shorterHeight = !shorterHeight;
    }
}

DisplayableRectObstacle
Obstacles::makeRandomObstacle(size_t scaledPointRange, size_t maxDimension, size_t minDimension,
        bool shorterWidth, bool shorterHeight) {
    DisplayableRectObstacle obstacle(scaledPointRange, maxDimension, minDimension,
            shorterWidth, shorterHeight);

    // make sure the newly created obstacle doesn't overlap with other obstacles or go off the screen
    bool invalidObs = true;
    while (invalidObs) {
        invalidObs = false;
        // is the obstacle going off the screen?
        if ((obstacle.getX_max() > scaledPointRange) || (obstacle.getY_max() > scaledPointRange)) {
            invalidObs = true;
            obstacle = DisplayableRectObstacle(scaledPointRange, maxDimension, minDimension,
                                               shorterWidth, shorterHeight);
            continue;
        }
        // does the obstacle overlap/intersect with any other obstacles?
        for (auto obs : existingObstacles) {
            if (obs.obstaclesOverlap(obstacle)) {
                obstacle = DisplayableRectObstacle(scaledPointRange, maxDimension, minDimension,
                        shorterWidth, shorterHeight);
                invalidObs = true;
                break;
            }
        }
    }

    return obstacle;
}
