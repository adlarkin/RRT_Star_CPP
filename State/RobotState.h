//
// Created by adlarkin on 10/29/18.
//

#ifndef RRT_PROJECT_ROBOTSTATE_H
#define RRT_PROJECT_ROBOTSTATE_H


#include <set>
#include "Location.h"

class RobotState {
public:
    RobotState(RobotState *parent, const Location &location);

public:

private:
    RobotState* parent;
    std::set<RobotState*> neighbors;
    Location location;
    int cost;
};


#endif //RRT_PROJECT_ROBOTSTATE_H