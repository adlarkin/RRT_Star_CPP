//
// Created by adlarkin on 1/14/19.
//

#include "DisplayableRectObstacle.h"
#include "../Location/Location.h"


#define PADDING_FACTOR .0025    // obstacle padding (percentage of total space)

DisplayableRectObstacle::DisplayableRectObstacle(size_t scaledPointRange, size_t maxDimension, size_t minDimension,
        bool shorterWidth, bool shorterHeight) : scaledPointRange(scaledPointRange) {
    obsPadding = (size_t)(scaledPointRange * PADDING_FACTOR);
    double widthFactor = 1.0;
    double heightFactor = 1.0;
    if (shorterWidth) {
        widthFactor = .5 * widthFactor;
    }
    if (shorterHeight) {
        heightFactor = .5 * heightFactor;
    }

    setMinMaxX(maxDimension, minDimension, widthFactor);
    setMinMaxY(maxDimension, minDimension, heightFactor);
}

void DisplayableRectObstacle::setMinMaxX(size_t maxDimension, size_t minDimension, double widthFactor) {
    size_t firstID = Location::makeIDFromPointRange(scaledPointRange);
    size_t secondID = Location::makeIDFromPointRange(scaledPointRange);
    x_min = std::min(firstID, secondID);
    x_max = std::max(firstID, secondID);
    if ((x_max - x_min) > maxDimension) {
        x_max = x_min + (size_t)(widthFactor * maxDimension);
    } else if ((x_max - x_min) < minDimension) {
        x_max = x_min + (size_t)(widthFactor * minDimension);
    }
}

void DisplayableRectObstacle::setMinMaxY(size_t maxDimension, size_t minDimension, double heightFactor) {
    size_t firstID = Location::makeIDFromPointRange(scaledPointRange);
    size_t secondID = Location::makeIDFromPointRange(scaledPointRange);
    y_min = std::min(firstID, secondID);
    y_max = std::max(firstID, secondID);
    if ((y_max - y_min) > maxDimension) {
        auto var = (size_t)(heightFactor * maxDimension);
        y_max = y_min + (size_t)(heightFactor * maxDimension);
    } else if ((y_max - y_min) < minDimension) {
        y_max = y_min + (size_t)(heightFactor * minDimension);
    }
}

size_t DisplayableRectObstacle::getPaddedX_Min() const {
    // checking for overflow
    if (x_min < obsPadding) {
        return 0;
    }
    return x_min - obsPadding;
}

size_t DisplayableRectObstacle::getPaddedX_Max() const {
    // checking for overflow
    if ((x_max + obsPadding) < x_max) {
        return scaledPointRange;
    }
    return x_max + obsPadding;
}

size_t DisplayableRectObstacle::getPaddedY_Min() const {
    // checking for overflow
    if (y_min < obsPadding) {
        return 0;
    }
    return y_min - obsPadding;
}

size_t DisplayableRectObstacle::getPaddedY_Max() const {
    // checking for overflow
    if ((y_max + obsPadding) < y_max) {
        return scaledPointRange;
    }
    return y_max + obsPadding;
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
    return (xID_other >= getPaddedX_Min()) && (xID_other <= getPaddedX_Max());
}

bool DisplayableRectObstacle::isInY(size_t yID_other) const {
    return (yID_other >= getPaddedY_Min()) && (yID_other <= getPaddedY_Max());
}

bool DisplayableRectObstacle::obstaclesOverlap(const DisplayableRectObstacle &otherObs) const {
    return ifCornersOverlap(otherObs) || ifEdgesOverlap(otherObs) ||
            otherObs.ifCornersOverlap(*this) || otherObs.ifEdgesOverlap(*this);
}

bool DisplayableRectObstacle::ifCornersOverlap(const DisplayableRectObstacle &otherObs) const {
    return (isInX(otherObs.x_min) && isInY(otherObs.y_min)) ||
           (isInX(otherObs.x_min) && isInY(otherObs.y_max)) ||
           (isInX(otherObs.x_max) && isInY(otherObs.y_min)) ||
           (isInX(otherObs.x_max) && isInY(otherObs.y_max));
}

bool DisplayableRectObstacle::ifEdgesOverlap(const DisplayableRectObstacle &otherObs) const {
    return ifHorizontalEdgeOverlaps(otherObs) || ifVerticalEdgeOverlaps(otherObs);
}

bool DisplayableRectObstacle::ifHorizontalEdgeOverlaps(const DisplayableRectObstacle &otherObs) const {
    return (x_min > otherObs.x_min) && (x_max < otherObs.x_max) &&
           (y_min < otherObs.y_min) && (y_max > otherObs.y_max);
}

bool DisplayableRectObstacle::ifVerticalEdgeOverlaps(const DisplayableRectObstacle &otherObs) const {
    return (x_min < otherObs.x_min) && (x_max > otherObs.x_max) &&
           (y_min > otherObs.y_min) && (y_max < otherObs.y_max);
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
