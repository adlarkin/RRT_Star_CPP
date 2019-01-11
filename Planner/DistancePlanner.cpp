//
// Created by ashton on 11/27/18.
//

#include <iostream>
#include "DistancePlanner.h"


DistancePlanner::DistancePlanner(const WindowParamsDTO &screenParams, size_t numPoints, double epsilon,
                                 int neighborhoodSize, double knnNeighborhoodRadiusFactor) :
        Planner(screenParams, numPoints, epsilon, neighborhoodSize, knnNeighborhoodRadiusFactor)
        {}

double DistancePlanner::cost(RobotState *startState, RobotState *endState) {
    return euclideanDistance(startState->getLocation(), endState->getLocation());
}

double DistancePlanner::cost(RobotState *startState, const Location &end) {
    return euclideanDistance(startState->getLocation(), end);
}

DistancePlanner::~DistancePlanner() {
    std::cout << "calling the distance planner's destructor..." << std::endl;
}
