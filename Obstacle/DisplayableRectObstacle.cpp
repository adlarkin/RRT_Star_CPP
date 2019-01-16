//
// Created by adlarkin on 1/14/19.
//

#include "DisplayableRectObstacle.h"
#include "../Location/Location.h"


DisplayableRectObstacle::DisplayableRectObstacle(size_t scaledPointRange, size_t maxDimension)
        : scaledPointRange(scaledPointRange) {
    size_t firstID = Location::makeIDFromPointRange(scaledPointRange);
    size_t secondID = Location::makeIDFromPointRange(scaledPointRange);
    size_t thirdID = Location::makeIDFromPointRange(scaledPointRange);
    size_t fourthID = Location::makeIDFromPointRange(scaledPointRange);

    x_min = std::min(firstID, secondID);
    x_max = std::max(firstID, secondID);
    if ((x_max - x_min) > maxDimension) {
        x_max = x_min + maxDimension;
    }
    y_min = std::min(thirdID, fourthID);
    y_max = std::max(thirdID, fourthID);
    if ((y_max - y_min) > maxDimension) {
        y_max = y_min + maxDimension;
    }
}

Location DisplayableRectObstacle::getTopLeftLoc() const {
    return Location(x_min, y_max, scaledPointRange);
}

bool DisplayableRectObstacle::isInX(const Location &location) const {
    return isInX(location.getX_ID());
}

bool DisplayableRectObstacle::isInY(const Location &location) const {
    return isInY(location.getY_ID());
}

bool DisplayableRectObstacle::isInX(size_t xID_other) const {
    return (xID_other >= x_min) && (xID_other <= x_max);
}

bool DisplayableRectObstacle::isInY(size_t yID_other) const {
    return (yID_other >= y_min) && (yID_other <= y_max);
}

bool DisplayableRectObstacle::obstaclesOverlap(const DisplayableRectObstacle &otherObs) const {
    // checking to see if one of the corners of otherObs is in 'this'
    return (isInX(otherObs.getX_min()) && isInY(otherObs.getY_min())) ||
            (isInX(otherObs.getX_min()) && isInY(otherObs.getY_max())) ||
            (isInX(otherObs.getX_max()) && isInY(otherObs.getY_min())) ||
            (isInX(otherObs.getX_max()) && isInY(otherObs.getY_max()));
}

size_t DisplayableRectObstacle::getX_min() const {
    return x_min;
}

size_t DisplayableRectObstacle::getX_max() const {
    return x_max;
}

size_t DisplayableRectObstacle::getY_min() const {
    return y_min;
}

size_t DisplayableRectObstacle::getY_max() const {
    return y_max;
}
