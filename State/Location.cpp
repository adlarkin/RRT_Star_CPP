//
// Created by adlarkin on 10/30/18.
//

#include "Location.h"

Location::Location(int maxIterations) :
    x(makeRandomPoint(maxIterations)),
    y(makeRandomPoint(maxIterations)) {}

float Location::getXCoord() const {
    return x.getCoordinate();
}

float Location::getYCoord() const {
    return y.getCoordinate();
}

BoostPoint Location::getBoostPoint() {
    return BoostPoint{x.getCoordinate(), y.getCoordinate()};
}

bool Location::operator==(const Location &rhs) const {
    return x.getID() == rhs.x.getID() &&
           y.getID() == rhs.y.getID();
}

bool Location::operator!=(const Location &rhs) const {
    return !(rhs == *this);
}

Point Location::makeRandomPoint(int pointValRange) {
    // the number of possible points to be sampled from
    // higher pointRange means less chance for randomly sampling duplicate points
    int pointRange = 4 * pointValRange;

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

    return Point{id, pos};
}
