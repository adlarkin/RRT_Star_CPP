//
// Created by adlarkin on 10/29/18.
//

#ifndef RRT_PROJECT_PLANNER_H
#define RRT_PROJECT_PLANNER_H

#include <set>
#include <unordered_set>
#include "../Utils/MyRtree.h"
#include "../Visualization/ShapeDrawer.h"

class Planner {
public:
    Planner(int numPoints, float epsilon);
    void findBestPath();
    virtual ~Planner(); // todo: smart pointers? (avoid deletion)

private:
    void pauseAnimation(int milliSec);

    RobotState* root;
    int maxIterations;
    float epsilon;
    Location start;
    Location end;
    ShapeDrawer drawer;
    MyRtree rtree;

    // saving all created states
    // this will make deleting pointers easy in the destructor
    std::unordered_set<RobotState*> allStates;
    // IGNORING UNIQUE LOCATIONS FOR NOW (I don't think it matters)
//    // this will also allow checking for duplicate locations
//    std::unordered_set<Location> allLocations;
};

#endif //RRT_PROJECT_PLANNER_H