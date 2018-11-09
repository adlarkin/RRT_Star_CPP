//
// Created by adlarkin on 10/29/18.
//

#include <GL/gl.h>
#include <iostream>
#include "Planner.h"
#include <set>
#include <chrono>
#include <thread>

Planner::Planner(int numPoints, float epsilon) :
        maxIterations(numPoints),
        epsilon(epsilon),
        start(makeRandomLocation(), makeRandomLocation()),
        end(makeRandomLocation(), makeRandomLocation()),
        drawer(.0125) {

    this->root = new RobotState(nullptr, this->start);  // the root state has no parent

    this->allStates.insert(root);
    // ensure that the start and end are different
    while (this->start == this->end) {
        this->end.changeCoords(makeRandomLocation(), makeRandomLocation());
    }
    this->allLocations.insert(this->start);
    this->allLocations.insert(this->end);

    rtree.add(root);
    drawer.updateScreen();  // this opens up an openGL screen with a black background
}

void Planner::findBestPath() {
    // draw the start and end points
    drawer.drawCircle(start, GREEN);
    drawer.drawCircle(end, BLUE);

    drawer.drawLine(start, end);
    drawer.drawRectangle(.3f, start, .1f);
    drawer.updateScreen();

    // wait half a second before showing the next line
    std::chrono::milliseconds waitTime(500);
    std::this_thread::sleep_for(waitTime);

    drawer.drawLine(Location(makeRandomLocation(), makeRandomLocation()),
            Location(makeRandomLocation(), makeRandomLocation()));
    drawer.updateScreen();

    // sometimes, the end BoostPoint is in the rectangle
    // redrawing the end BoostPoint to make sure it's not off the screen (this is for testing)
    drawer.drawCircle(end, BLUE);
    drawer.updateScreen();

    int iterations = 0;
    while (allStates.size() < maxIterations) {
        // todo: write the rrt* code here (use rTree?)
        // todo: no obstacles first. add obstacles after the planner works w/o them
        break;
    }
}

float Planner::makeRandomLocation() {
    // the number of possible points to be sampled from
    // higher pointRange means less chance for randomly sampling duplicate points
    int pointRange = 4 * this->maxIterations;

    // make a number between 0 and pointRange, exclusive
    // this number is the id of the coordinate
    // (using int IDs to compare with other coordinates for duplicates)
    int id = rand() % pointRange;

    /*
     * turn this number into a float between -1 and 1 (coordinate range for openGL)
     * this is done the following way:
     * 1) divide id by pointRange
     *    this will give a float between 0 and 1
     * 2) multiply this new float by 2 to get a float between 0 and 2
     * 3) subtract 1 from it to get a float between -1 and 1
     */
    float pos = (((float)id / pointRange) * 2) - 1;

    return pos;
}

Planner::~Planner() {
    for (auto state : allStates) {
        delete state;
        state = nullptr;
    }
}
