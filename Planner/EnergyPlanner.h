//
// Created by ashton on 11/27/18.
//

#ifndef RRT_STAR_CPP_ENERGYPLANNER_H
#define RRT_STAR_CPP_ENERGYPLANNER_H


#include "Planner.h"

class EnergyPlanner : public Planner {
public:
    EnergyPlanner(int numPoints, float epsilon);
    double cost(RobotState *startState, RobotState *endState) override;
};


#endif //RRT_STAR_CPP_ENERGYPLANNER_H
