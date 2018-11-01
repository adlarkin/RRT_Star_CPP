//
// Created by adlarkin on 10/29/18.
//

#ifndef RRT_PROJECT_PLANNER_H
#define RRT_PROJECT_PLANNER_H

#include <set>
#include "../State/RobotState.h"
#include "../State/Location.h"
#include "../State/Coordinate.h"

// todo: have functions for drawing (circle, line, obstacle ... take in a color too?)
// todo: verify that locations are being checked correctly for uniqueness

class Planner {
public:
    virtual ~Planner();

    Planner(int numPoints, float epsilon);
    void print();

private:
    Coordinate makeRandomCoordinate();

    RobotState* root;
    int maxIterations;
    float epsilon;
    Location start;
    Location end;

    // saving all created states and locations
    // this will make deleting pointers easy in the destructor
    // this will also allow checking for duplicate locations
    std::set<RobotState*> allStates;
    std::set<Location*> allLocations;
};


#endif //RRT_PROJECT_PLANNER_H