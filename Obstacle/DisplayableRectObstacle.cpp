//
// Created by adlarkin on 1/14/19.
//

#include "DisplayableRectObstacle.h"
#include "../Location/Location.h"

DisplayableRectObstacle::DisplayableRectObstacle(size_t scaledPointRange) : scaledPointRange(scaledPointRange) {
    size_t firstID = Location::makeIDFromPointRange(scaledPointRange);
    size_t secondID = Location::makeIDFromPointRange(scaledPointRange);
    size_t thirdID = Location::makeIDFromPointRange(scaledPointRange);
    size_t fourthID = Location::makeIDFromPointRange(scaledPointRange);

    x_min = std::min(firstID, secondID);
    x_max = std::max(firstID, secondID);
    y_min = std::min(thirdID, fourthID);
    y_max = std::max(thirdID, fourthID);
}

Location DisplayableRectObstacle::getTopLeftLoc() const {
    return Location(x_min, y_max, scaledPointRange);
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
