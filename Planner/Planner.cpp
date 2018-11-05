//
// Created by adlarkin on 10/29/18.
//

#include <GL/gl.h>
#include <iostream>
#include "Planner.h"
#include "../State/Coordinate.h"
#include <set>
#include <chrono>
#include <thread>

Planner::Planner(int numPoints, float epsilon) :
        maxIterations(numPoints),
        epsilon(epsilon),
        start(makeRandomCoordinate(), makeRandomCoordinate()),
        end(makeRandomCoordinate(), makeRandomCoordinate()),
        drawer(.0125) {

    this->root = new RobotState(nullptr, this->start);  // the root state has no parent

    this->allStates.insert(root);
    this->allLocations.insert(this->start);
    this->allLocations.insert(this->end);

    glFlush();
}

void Planner::findBestPath() {
    // draw the start and end points
    drawer.drawCircle(start, GREEN);
    drawer.drawCircle(end, BLUE);

    drawer.drawLine(start, end);
    drawer.drawRectangle(.3f, start, .1f);

    /*
    // wait half a second before showing the next line
    std::chrono::milliseconds waitTime(500);
    std::this_thread::sleep_for(waitTime);
    */

    drawer.drawLine(Location(makeRandomCoordinate(), makeRandomCoordinate()),
            Location(makeRandomCoordinate(), makeRandomCoordinate()));
    glFlush();

    while (allStates.size() < maxIterations) {
        // todo: write the rrt* code here
        break;
    }
}

Coordinate Planner::makeRandomCoordinate() {
    int pointRange = 2 * this->maxIterations;

    // make a number between 0 and pointRange, exclusive
    // this number is the id of the coordinate
    // (using int IDs to compare with other coordinates for duplicates)
    int id = rand() % pointRange;

    /*
     * turn this number into a float between -1 and 1 (needed for openGL)
     * this is done the following way:
     * 1) divide id by pointRange
     *    this will give a float between 0 and 1
     * 2) multiply this new float by 2 to get a float between 0 and 2
     * 3) subtract 1 from it to get a float between -1 and 1
     */
    float pos = (((float)id / pointRange) * 2) - 1;

    return Coordinate{id, pos};
}

Planner::~Planner() {
    for (auto state : allStates) {
        delete state;
        state = nullptr;
    }
}