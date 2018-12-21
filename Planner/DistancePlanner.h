//
// Created by ashton on 11/27/18.
//

#ifndef RRT_STAR_CPP_DISTANCEPLANNER_H
#define RRT_STAR_CPP_DISTANCEPLANNER_H


#include "Planner.h"

class DistancePlanner : public Planner {
public:
    DistancePlanner(WindowParamsDTO screenParams, int numPoints, double epsilon);
    double cost(RobotState *startState, RobotState *endState) override;
};


#endif //RRT_STAR_CPP_DISTANCEPLANNER_H
