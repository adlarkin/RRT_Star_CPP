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
    Planner(const WindowParamsDTO &screenParams, int numPoints, double epsilon);
    void findBestPath();
    virtual ~Planner(); // todo: smart pointers? (avoid deletion)

protected:
    // the cost method will be determined by the type of planner object that is constructed
    virtual double cost(RobotState *startState, RobotState *endState) = 0;
    double euclideanDistance(const Location &start, const Location &end);

private:
    void updatePath(RobotState *possibleSolution, size_t &pathsFound);
    RobotState * rewire(RobotState *nearest, const Location &nextLocation);
    void updateNeighboringStateCosts(RobotState *parent);
    Location makeUniqueLocation();
    Location makeLocationWithinEpsilon(RobotState *nearest, const Location &location);
    RobotState* createNewState(RobotState *parent, const Location &location);
    bool isInGoalSpace(RobotState *mostRecentState);
    void showPath(RobotState *lastState);
    void redrawTree(RobotState *beginningState);
    void pauseAnimation(int milliSec);
    void showStartAndGoal();

    // saving all created states and locations
    // this will make deleting pointers easy in the destructor
    // this will also allow checking for duplicate locations
    std::vector<RobotState*> allStates;
    std::unordered_set<Location> allLocations;

    RobotState* root;
    int maxIterations;
    double epsilon;
    Location start;
    Location goal;
    MyRtree rTree;
    Drawer drawer;

    RobotState* currSolutionState;
    double bestCostSoFar;
};

#endif //RRT_PROJECT_PLANNER_H