//
// Created by adlarkin on 10/29/18.
//

#ifndef RRT_PROJECT_PLANNER_H
#define RRT_PROJECT_PLANNER_H

#include <set>
#include <unordered_set>
#include "../Utils/MyRtree.h"
#include "../Visualization/Drawer.h"
#include "../Obstacle/Obstacles.h"

class Planner {
public:
    Planner(const WindowParamsDTO &screenParams, size_t numPoints, double epsilon, int neighborhoodSize,
            double knnNeighborhoodRadiusFactor);
    void findBestPath();
    virtual ~Planner();

protected:
    // the cost method will be determined by the type of planner object that is constructed
    virtual double cost(RobotState *startState, RobotState *endState) = 0;
    virtual double cost(RobotState* startState, const Location &end) = 0;
    double euclideanDistance(const Location &start, const Location &end);

private:
    void updatePath(size_t &pathsFound);
    void rewire(RobotState *nearest, const Location &nextLocation);
    void updateNeighboringStateCosts(RobotState *parent);
    Location makeUniqueObstacleFreeLocation();
    bool isObstacleFree(const Location& location) const;
    Location makeLocationWithinEpsilon(RobotState *nearest, const Location &location);
    RobotState* createNewState(RobotState *parent, const Location &location);
    void showPath(RobotState *lastState);
    void redrawTree(RobotState *beginningState);
    void pauseAnimation(int milliSec);
    void showStartAndGoal();
    void drawObstacles();

    // saving all created states and locations
    // this will make deleting pointers easy in the destructor
    // this will also allow checking for duplicate locations
    std::vector<RobotState*> allStates;
    std::unordered_set<Location> allLocations;

    RobotState* root;
    size_t maxIterations;
    double epsilon;
    int neighborhoodSize;
    double knnNeighborhoodRadius;
    Obstacles obstacles;
    Location start;
    Location goal;
    MyRtree rTree;
    Drawer drawer;

    RobotState* currSolutionState;
    double bestCostSoFar;
};

#endif //RRT_PROJECT_PLANNER_H