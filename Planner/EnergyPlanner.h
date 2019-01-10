//
// Created by ashton on 11/27/18.
//

#ifndef RRT_STAR_CPP_ENERGYPLANNER_H
#define RRT_STAR_CPP_ENERGYPLANNER_H


#include "Planner.h"

class EnergyPlanner : public Planner {
public:
    EnergyPlanner(const WindowParamsDTO &screenParams, int numPoints, double epsilon, int neighborhoodSize,
                  double knnNeighborhoodRadiusFactor);
    virtual ~EnergyPlanner();

protected:
    double cost(RobotState *startState, RobotState *endState) override;
    double cost(RobotState *startState, const Location &end) override;
};


#endif //RRT_STAR_CPP_ENERGYPLANNER_H
