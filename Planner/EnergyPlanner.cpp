//
// Created by ashton on 11/27/18.
//

#include <iostream>
#include "EnergyPlanner.h"

EnergyPlanner::EnergyPlanner(const WindowParamsDTO &screenParams, size_t numPoints, double epsilon,
                             int neighborhoodSize, double knnNeighborhoodRadiusFactor) :
        Planner(screenParams, numPoints, epsilon, neighborhoodSize, knnNeighborhoodRadiusFactor)
        {}

double EnergyPlanner::cost(RobotState *startState, RobotState *endState) {
    // todo: fill this in (using euclidean distance for now so that I have something)!
    return euclideanDistance(startState->getLocation(), endState->getLocation());
}

double EnergyPlanner::cost(RobotState *startState, const Location &end) {
    // todo: fill this in (using euclidean distance for now so that I have something)!
    return euclideanDistance(startState->getLocation(), end);
}

EnergyPlanner::~EnergyPlanner() {
    std::cout << "calling the energy planner's destructor..." << std::endl;
}
