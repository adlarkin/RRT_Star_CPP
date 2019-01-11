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
#define PATH_COLOR PINK
#define PATH_WIDTH 3.5f

// initializer lists init objects based on the order they're declared in the .h file
// allLocations must be initialized before start/goal in order for makeUniqueLocation() to work
Planner::Planner(const WindowParamsDTO &screenParams, size_t numPoints, double epsilon, int neighborhoodSize,
                 double knnNeighborhoodRadiusFactor) :
        maxIterations(numPoints),
        epsilon(epsilon),
        neighborhoodSize(neighborhoodSize),
        knnNeighborhoodRadius(knnNeighborhoodRadiusFactor * epsilon),
        start(makeUniqueLocation()),
        goal(makeUniqueLocation()),
        drawer(screenParams)    // initializing the drawer also sets up a blank screen
        {
    this->root = createNewState(nullptr, this->start);  // the root state has no parent

    currSolutionState = nullptr;
    bestCostSoFar = std::numeric_limits<double>::infinity();
}

void Planner::findBestPath() {
    // let the client see the start and goal points
    showStartAndGoal();
    drawer.updateScreen();
    pauseAnimation(500);

    size_t numBetterPathsFound = 0;
    while (allStates.size() < maxIterations) {
        Location sampledLoc = makeUniqueLocation();
        RobotState* nearest = rTree.getNearestElement(sampledLoc);
        if (euclideanDistance(nearest->getLocation(), sampledLoc) > epsilon) {
            sampledLoc = makeLocationWithinEpsilon(nearest, sampledLoc);
        }
        RobotState* nextState = rewire(nearest, sampledLoc);
        updatePath(nextState, numBetterPathsFound);
        drawer.updateScreen();
    }

    std::cout << std::endl << "Found a total of " << numBetterPathsFound << " paths" << std::endl;
    drawer.keepScreenOpen();    // let the client see the (possible) resulting path
}

void Planner::updatePath(RobotState *possibleSolution, size_t &pathsFound) {
    bool foundBetterPath = false;

    // is there a better path, and if so, is that from the same or different solution state?
    if ((currSolutionState != nullptr) && (currSolutionState->getCost() < bestCostSoFar)) {
        // rewiring created a better way to get to the current solution state
        foundBetterPath = true;
    }
    if ((possibleSolution->getCost() < bestCostSoFar) && isInGoalSpace(possibleSolution)) {
        // the new state is a valid one with a better cost than the current solution state
        currSolutionState = possibleSolution;
        foundBetterPath = true;
    }

    if (foundBetterPath) {
        // update the cost and redraw the tree to make the rewiring more clear
        // (sometimes, erasing old connections can (partially) erase other valid connections)
        bestCostSoFar = currSolutionState->getCost();
        drawer.clearScreen();
        redrawTree(root);
        pathsFound++;
        std::cout << "PATH FOUND! Cost is: " << bestCostSoFar << std::endl;
    }

    // redraw the path in case newly created connections drew over it
    if (currSolutionState != nullptr) {
        showPath(currSolutionState);
    }
}

double Planner::euclideanDistance(const Location &start, const Location &end) {
    double xDiff = end.getXCoord() - start.getXCoord();
    double yDiff = end.getYCoord() - start.getYCoord();
    return sqrt((xDiff * xDiff) + (yDiff * yDiff));
}

RobotState * Planner::rewire(RobotState *nearest, const Location &nextLocation) {
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
            updateNeighboringStateCosts(state); // todo: see if this is really needed
            // todo: make sure the old parent isn't an empty node? (this shouldn't happen, just think about it some more)
        }
    }

    showStartAndGoal(); // re-draw the start/goal in case lines drew over them
    return nextState;
}

void Planner::updateNeighboringStateCosts(RobotState *parent) {
    std::unordered_set<RobotState*> oldCostStates = parent->getNeighbors();
    for (auto state : oldCostStates) {
        state->setCost(parent->getCost() + cost(parent, state));
        updateNeighboringStateCosts(state);
    }
}

Location Planner::makeUniqueLocation() {
    Location location(maxIterations);
    while (allLocations.count(location)) {
        location = Location(maxIterations);
    }
    allLocations.insert(location);
    return location;
}

Location Planner::makeLocationWithinEpsilon(RobotState *nearest, const Location &location) {
    allLocations.erase(location);   // remove the location outside of epsilon since it's not valid
    double yDiff = location.getYCoord() - nearest->getLocation().getYCoord();
    double xDiff = location.getXCoord() - nearest->getLocation().getXCoord();
    double theta = atan2(yDiff, xDiff);    // in radians
    double xCoord = nearest->getLocation().getXCoord() + (epsilon * cos(theta));
    double yCoord = nearest->getLocation().getYCoord() + (epsilon * sin(theta));
    Location updatedLocation(xCoord, yCoord, maxIterations);
    allLocations.insert(updatedLocation);
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

bool Planner::isInGoalSpace(RobotState *mostRecentState) {
    return euclideanDistance(mostRecentState->getLocation(), goal) <= epsilon;
}

void Planner::showPath(RobotState *lastState) {
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

//    drawer.deleteScreen();

    for (auto state : allStates) {
        delete state;
        state = nullptr;
    }
}

void Planner::showStartAndGoal() {
    drawer.drawCircle(start, START_COLOR, CIRCLE_RADIUS);
    drawer.drawCircle(goal, GOAL_COLOR, CIRCLE_RADIUS);
}
