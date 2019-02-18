//
// Created by adlarkin on 10/29/18.
//

//#include <GL/gl.h>
#include <iostream>
#include "Planner.h"
#include <set>
#include <chrono>
#include <thread>

#define CIRCLE_RADIUS .0085
#define START_COLOR GREEN
#define GOAL_COLOR RED
#define LINE_COLOR GREY
#define PATH_COLOR LIGHT_BLUE
#define PATH_WIDTH 1.5f
#define NUM_OBSTACLES 20
#define OBSTACLE_COLOR WHITE

// initializer lists init objects based on the order they're declared in the .h file
// allLocations must be initialized before start/goal in order for makeUniqueObstacleFreeLocation() to work
Planner::Planner(const WindowParamsDTO &screenParams, size_t numPoints, double epsilon, int neighborhoodSize,
                 double knnNeighborhoodRadiusFactor) :
        maxIterations(numPoints),
        epsilon(epsilon),
        neighborhoodSize(neighborhoodSize),
        knnNeighborhoodRadius(knnNeighborhoodRadiusFactor * epsilon),
        obstacles(Location::getScaledPointRange(numPoints), NUM_OBSTACLES),
        start(makeUniqueObstacleFreeLocation()),
        goal(makeUniqueObstacleFreeLocation()),
        drawer(screenParams)    // initializing the drawer also sets up a blank screen
        {
    this->root = createNewState(nullptr, this->start);  // the root state has no parent

    currSolutionState = nullptr;
    bestCostSoFar = std::numeric_limits<double>::infinity();
}

void Planner::findBestPath() {
    drawObstacles();
    showStartAndGoal(); // let the client see the start and goal points
    drawer.updateScreen();
    pauseAnimation(500);

    size_t numBetterPathsFound = 0;
    while (allStates.size() < maxIterations) {
        Location sampledLoc = makeUniqueObstacleFreeLocation();
        RobotState* nearest = rTree.getNearestElement(sampledLoc);
        if (euclideanDistance(nearest->getLocation(), sampledLoc) > epsilon) {
            sampledLoc = makeLocationWithinEpsilon(nearest, sampledLoc);
            // makeLocationWithinEpsilon() may make a new location that isn't obstacle free
            if (!isObstacleFree(sampledLoc)) {
                continue;
            }
        }
        rewire(nearest, sampledLoc);
        updatePath(numBetterPathsFound);
        drawer.updateScreen();
    }

    // update the screen one last time now that the algorithm is complete
    drawer.clearScreen();
    drawObstacles();
    redrawTree(root);
    showPath(currSolutionState);
    std::cout << std::endl << "Found a total of " << numBetterPathsFound << " paths" << std::endl;
    std::cout << "The straight line euclidean distance cost is " << euclideanDistance(start, goal) << std::endl;
    drawer.keepScreenOpen();    // let the client see the (possible) resulting path
}

void Planner::updatePath(size_t &pathsFound) {
    // see if any states within epsilon of the goal state are a better solution due to rewiring
    bool foundBetterPath = false;
    std::vector<RobotState*> solutionCandidates = rTree.getKNearestNeighbors(goal, neighborhoodSize,
            knnNeighborhoodRadius);
    for (auto candidate : solutionCandidates) {
        if (candidate->getCost() < bestCostSoFar) {
            currSolutionState = candidate;
            bestCostSoFar = candidate->getCost();
            foundBetterPath = true;
        }
    }

    if (foundBetterPath) {
        pathsFound++;
        // redraw the tree to make the rewiring more clear
        // (sometimes, erasing old connections can (partially) erase other valid connections)
        drawer.clearScreen();
        drawObstacles();
        redrawTree(root);
        std::cout << "PATH FOUND! Cost is: " << bestCostSoFar << std::endl;
    }

    // redraw the path in case newly created connections drew over it
    showPath(currSolutionState);
}

double Planner::euclideanDistance(const Location &start, const Location &end) {
    double xDiff = end.getXCoord() - start.getXCoord();
    double yDiff = end.getYCoord() - start.getYCoord();
    return sqrt((xDiff * xDiff) + (yDiff * yDiff));
}

void Planner::rewire(RobotState *nearest, const Location &nextLocation) {
    double minCost = nearest->getCost() + cost(nearest, nextLocation);
    std::vector<RobotState*> stateNeighborhood =
            rTree.getKNearestNeighbors(nextLocation, neighborhoodSize, knnNeighborhoodRadius);
    // connect along a minimum-cost path
    for (auto state : stateNeighborhood) {
        double tempCost = state->getCost() + cost(state, nextLocation);
        if (tempCost < minCost) {
            nearest = state;
            minCost = tempCost;
        }
    }
    RobotState* nextState = createNewState(nearest, nextLocation);
    drawer.drawLine(nearest->getLocation(), nextLocation, LINE_COLOR);

    // re-wire the tree
    for (auto state : stateNeighborhood) {
        double tempCost = nextState->getCost() + cost(nextState, state);
        if (tempCost < state->getCost()) {
            // update the parent of 'state' to the newly created state
            drawer.eraseLine(state->getLocation(), state->getParent()->getLocation());
            state->updateParent(nextState, tempCost);
            drawer.drawLine(state->getLocation(), state->getParent()->getLocation(), LINE_COLOR);
            updateNeighboringStateCosts(state);
        }
    }

    showStartAndGoal(); // re-draw the start/goal in case lines drew over them
}

void Planner::updateNeighboringStateCosts(RobotState *parent) {
    std::unordered_set<RobotState*> oldCostStates = parent->getNeighbors();
    for (auto state : oldCostStates) {
        state->setCost(parent->getCost() + cost(parent, state));
        updateNeighboringStateCosts(state);
    }
}

Location Planner::makeUniqueObstacleFreeLocation() {
    Location location(maxIterations);
    while ((!isObstacleFree(location)) || allLocations.count(location)) {
        location = Location(maxIterations);
    }
    allLocations.insert(location);
    return location;
}

bool Planner::isObstacleFree(const Location &location) const {
    return obstacles.isObstacleFree(location);
}

Location Planner::makeLocationWithinEpsilon(RobotState *nearest, const Location &location) {
    allLocations.erase(location);   // remove the location outside of epsilon since it's not valid
    double yDiff = location.getYCoord() - nearest->getLocation().getYCoord();
    double xDiff = location.getXCoord() - nearest->getLocation().getXCoord();
    double theta = atan2(yDiff, xDiff);    // in radians
    double xCoord = nearest->getLocation().getXCoord() + (epsilon * cos(theta));
    double yCoord = nearest->getLocation().getYCoord() + (epsilon * sin(theta));
    Location updatedLocation(xCoord, yCoord, maxIterations);
    if (isObstacleFree(updatedLocation)) {
        allLocations.insert(updatedLocation);
    }
    return updatedLocation;
}

RobotState *Planner::createNewState(RobotState *parent, const Location &location) {
    auto nextState = new RobotState(parent, location);
    // the root state has a cost of 0
    nextState->setCost(0);
    // if nextState is not the root state, adjust the cost accordingly
    if (parent != nullptr) {
        nextState->setCost(parent->getCost() + cost(parent, nextState));
        parent->addNeighbor(nextState);
    }
    allStates.push_back(nextState);
    rTree.add(nextState);
    return nextState;
}

void Planner::showPath(RobotState *lastState) {
    if (lastState == nullptr) {
        return;
    }

    while (lastState != root) {
        RobotState* next = lastState->getParent();
        drawer.drawLine(lastState->getLocation(), next->getLocation(), PATH_COLOR, PATH_WIDTH);
        lastState = next;
    }
    // redraw the start/goal points so that the path doesn't display over them
    showStartAndGoal();
}

void Planner::redrawTree(RobotState *beginningState) {
    std::unordered_set<RobotState*> connectingStates = beginningState->getNeighbors();
    for (auto state : connectingStates) {
        drawer.drawLine(beginningState->getLocation(), state->getLocation(), LINE_COLOR);
        redrawTree(state);
    }
}

void Planner::pauseAnimation(int milliSec) {
    // wait for a num. of milliseconds before doing the next thing
    std::chrono::milliseconds waitTime(milliSec);
    std::this_thread::sleep_for(waitTime);
}

Planner::~Planner() {
    std::cout << "calling the generic planner's destructor..." << std::endl;

    for (auto state : allStates) {
        delete state;
        state = nullptr;
    }
}

void Planner::showStartAndGoal() {
    drawer.drawCircle(start, START_COLOR, CIRCLE_RADIUS);
    drawer.drawCircle(goal, GOAL_COLOR, CIRCLE_RADIUS);
}

void Planner::drawObstacles() {
    std::vector<DisplayableRectObstacle> existingObs = obstacles.getExistingObstacles();
    for (auto ob : existingObs) {
        Location topRight(ob.getX_max(), ob.getY_max(), Location::getScaledPointRange(maxIterations));
        double width = euclideanDistance(ob.getTopLeftLoc(), topRight);
        Location bottomLeft(ob.getX_min(), ob.getY_min(), Location::getScaledPointRange(maxIterations));
        double height = euclideanDistance(ob.getTopLeftLoc(), bottomLeft);
        drawer.drawRectangle(width, ob.getTopLeftLoc(), height, OBSTACLE_COLOR);
    }
}
