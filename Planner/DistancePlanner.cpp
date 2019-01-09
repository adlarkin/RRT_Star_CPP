//
// Created by ashton on 11/27/18.
//

#include "DistancePlanner.h"

DistancePlanner::DistancePlanner(const WindowParamsDTO &screenParams, int numPoints, double epsilon) :
    Planner(screenParams, numPoints, epsilon)
    {}

double DistancePlanner::cost(RobotState *startState, RobotState *endState) {
    return euclideanDistance(startState->getLocation(), endState->getLocation());
}