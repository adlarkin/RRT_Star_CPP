//
// Created by ashton on 11/27/18.
//

#include "EnergyPlanner.h"

EnergyPlanner::EnergyPlanner(const WindowParamsDTO &screenParams, int numPoints, double epsilon) :
    Planner(screenParams, numPoints, epsilon)
    {}

double EnergyPlanner::cost(RobotState *startState, RobotState *endState) {
    // todo: fill this in (using euclidean distance for now so that I have something)!
    return euclideanDistance(startState->getLocation(), endState->getLocation());
}
