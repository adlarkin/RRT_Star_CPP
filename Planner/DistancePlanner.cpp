//
// Created by ashton on 11/27/18.
//

#include "DistancePlanner.h"

DistancePlanner::DistancePlanner(int numPoints, double epsilon) : Planner(numPoints, epsilon) {}

double DistancePlanner::cost(RobotState *startState, RobotState *endState) {
    // cost is euclidean distance
    double xDiff = endState->getLocation().getXCoord() - startState->getLocation().getXCoord();
    double yDiff = endState->getLocation().getYCoord() - startState->getLocation().getYCoord();
    return sqrt((xDiff * xDiff) + (yDiff * yDiff));
}