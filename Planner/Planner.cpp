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
#define END_COLOR RED
#define LINE_COLOR WHITE
#define PATH_COLOR LIGHT_BLUE
#define NEIGHBORHOOD_SIZE 10

// initializer lists init objects based on the order they're declared in the .h file
// allLocations must be initialized before start/end in order for makeUniqueLocation() to work
Planner::Planner(WindowParamsDTO screenParams, int numPoints, double epsilon) :
        maxIterations(numPoints),
        epsilon(epsilon),
        start(makeUniqueLocation()),
        end(makeUniqueLocation()),
        drawer(screenParams)    // initializing the drawer also sets up a blank screen
        {
    this->root = createNewState(nullptr, this->start);  // the root state has no parent

    // todo: USE THESE
    currSolutionState = nullptr;
    bestCostSoFar = std::numeric_limits<double>::infinity();
}

void Planner::findBestPath() {
    // draw the start and end points
    drawer.drawCircle(start, START_COLOR, CIRCLE_RADIUS);
    drawer.drawCircle(end, END_COLOR, CIRCLE_RADIUS);
    drawer.updateScreen();
    pauseAnimation(500);    // let the client see the start and end points

    while (allStates.size() < maxIterations) {
        Location sampledLoc = makeUniqueLocation();
        RobotState* nearest = rTree.getNearestElement(sampledLoc);
        if (euclideanDistance(nearest->getLocation(), sampledLoc) > epsilon) {
            sampledLoc = makeLocationWithinEpsilon(nearest, sampledLoc);
        }
        RobotState* nextState = rewire(nearest, sampledLoc);
        if (foundPath(nextState)) {
            displayPath(nextState);
            std::cout << "PATH FOUND! Cost is: " << nextState->getCost() << std::endl;
        }
    }

    drawer.keepScreenOpen();    // let the client see the (possible) resulting path
}

double Planner::euclideanDistance(Location start, Location end) {
    double xDiff = end.getXCoord() - start.getXCoord();
    double yDiff = end.getYCoord() - start.getYCoord();
    return sqrt((xDiff * xDiff) + (yDiff * yDiff));
}

RobotState * Planner::rewire(RobotState *nearest, Location nextLocation) {
    // todo: use polymorphic cost function instead of euclidean distance for minCost (create a cost(state, location) method?)
    // todo: the above line requires changes in the below lines for minCost and tempCost
    double minCost = nearest->getCost() + euclideanDistance(nearest->getLocation(), nextLocation);
    std::vector<RobotState*> stateNeighborhood =
            rTree.getKNearestNeighbors(nextLocation, NEIGHBORHOOD_SIZE, epsilon);
    // connect along a minimum-cost path
    for (auto state : stateNeighborhood) {
        double tempCost = state->getCost() + euclideanDistance(state->getLocation(), nextLocation);
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
            // (make sure we remove the old connection in the visualization as well)
            drawer.drawLine(state->getLocation(), state->getParent()->getLocation(), BLACK);
            state->updateParent(nextState, tempCost);
            drawer.drawLine(state->getLocation(), state->getParent()->getLocation(), LINE_COLOR);
            updateNeighboringStateCosts(state); // todo: see if this is really needed
            // todo: make sure the old parent isn't an empty node? (this shouldn't happen, just think about it some more)
        }
    }

    // re-draw the start/end in case lines drew over them
    drawer.drawCircle(start, START_COLOR, CIRCLE_RADIUS);
    drawer.drawCircle(end, END_COLOR, CIRCLE_RADIUS);
    drawer.updateScreen();
    
    return nextState;
}

void Planner::updateNeighboringStateCosts(RobotState *parent) {
    std::vector<RobotState*> oldCostStates = parent->getNeighbors();
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

Location Planner::makeLocationWithinEpsilon(RobotState *nearest, Location location) {
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

RobotState *Planner::createNewState(RobotState *parent, Location location) {
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

bool Planner::foundPath(RobotState *mostRecentState) {
    if (euclideanDistance(mostRecentState->getLocation(), end) <= epsilon) {
        return true;
    }
    return false;
}

void Planner::displayPath(RobotState *lastState) {
    // this clears the old path (if one exists) and makes the re-wiring more clear
    // (sometimes, black lines that are drawn to erase old parents override connections that still exist)
    drawer.clearScreen();
    redrawTree(root);

    while (lastState != root) {
        RobotState* next = lastState->getParent();
        drawer.drawLine(lastState->getLocation(), next->getLocation(), PATH_COLOR, 4.5f);
        lastState = next;
    }
    // redraw the start/end points so that the path doesn't display over them
    drawer.drawCircle(start, START_COLOR, CIRCLE_RADIUS);
    drawer.drawCircle(end, END_COLOR, CIRCLE_RADIUS);
    drawer.updateScreen();
}

void Planner::redrawTree(RobotState *beginningState) {
    std::vector<RobotState*> connectingStates = beginningState->getNeighbors();
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

// TODO: make sure this gets called ... do I need to put destructors in the child classes too?
Planner::~Planner() {
    drawer.deleteScreen();

    for (auto state : allStates) {
        delete state;
        state = nullptr;
    }
}
