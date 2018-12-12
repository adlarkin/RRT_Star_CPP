//
// Created by ashton on 11/27/18.
//

#include "DistancePlanner.h"

DistancePlanner::DistancePlanner(int numPoints, double epsilon) : Planner(numPoints, epsilon) {}

double DistancePlanner::cost(RobotState *startState, RobotState *endState) {
    return euclideanDistance(startState->getLocation(), endState->getLocation());
}