//
// Created by adlarkin on 10/29/18.
//

#ifndef RRT_PROJECT_PLANNER_H
#define RRT_PROJECT_PLANNER_H

#include <set>
#include <unordered_set>
#include "../Utils/MyRtree.h"
#include "../Visualization/Drawer.h"

class Planner {
public:
    Planner(WindowParamsDTO screenParams, int numPoints, double epsilon);
    void findBestPath();
    virtual ~Planner(); // todo: smart pointers? (avoid deletion)

protected:
    // the cost method will be determined by the type of planner object that is constructed
    virtual double cost(RobotState *startState, RobotState *endState) = 0;
    double euclideanDistance(Location start, Location end);

private:
    Location makeUniqueLocation();
    Location makeLocationWithinEpsilon(RobotState *nearest, Location location);
    RobotState* createNewState(RobotState* parent, Location location);
    bool foundPath(RobotState* mostRecentState);
    void displayPath(RobotState* lastState);
    void pauseAnimation(int milliSec);

    // saving all created states and locations
    // this will make deleting pointers easy in the destructor
    // this will also allow checking for duplicate locations
    std::vector<RobotState*> allStates;
    std::unordered_set<Location> allLocations;

    RobotState* root;
    int maxIterations;
    double epsilon;
    Location start;
    Location end;
    MyRtree rTree;
    Drawer drawer;
};

#endif //RRT_PROJECT_PLANNER_H