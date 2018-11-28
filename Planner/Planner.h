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

protected:
    // the cost method will be determined by the type of planner object that is constructed
    virtual double cost(RobotState *startState, RobotState *endState) = 0;

private:
    Location makeUniqueLocation();
    RobotState* createNewState(RobotState* parent, Location location);
    void pauseAnimation(int milliSec);
    void randomTestCode();  // todo: remove this later

    // saving all created states and locations
    // this will make deleting pointers easy in the destructor
    // this will also allow checking for duplicate locations
    std::unordered_set<RobotState*> allStates;
    std::unordered_set<Location> allLocations;

    RobotState* root;
    int maxIterations;
    float epsilon;
    Location start;
    Location end;
    ShapeDrawer drawer;
    MyRtree rTree;
};

#endif //RRT_PROJECT_PLANNER_H