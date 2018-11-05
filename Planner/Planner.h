//
// Created by adlarkin on 10/29/18.
//

#ifndef RRT_PROJECT_PLANNER_H
#define RRT_PROJECT_PLANNER_H

#include <set>
#include <unordered_set>
#include "../State/RobotState.h"
#include "../State/Location.h"
#include "../State/Coordinate.h"
#include "../Utils/ObjHashes.cpp"
#include "../Visualization/ShapeDrawer.h"


class Planner {
public:
    virtual ~Planner();

    Planner(int numPoints, float epsilon);
    void findBestPath();

private:
    Coordinate makeRandomCoordinate();

    RobotState* root;
    int maxIterations;
    float epsilon;
    Location start;
    Location end;

    ShapeDrawer drawer;

    // saving all created states and locations
    // this will make deleting pointers easy in the destructor
    // this will also allow checking for duplicate locations
    std::unordered_set<RobotState*> allStates;
    std::unordered_set<Location> allLocations;
};


#endif //RRT_PROJECT_PLANNER_H