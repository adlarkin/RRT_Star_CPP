//
// Created by adlarkin on 10/30/18.
//

#include "Location.h"
#include <random>

#define SCALING_FACTOR 4

Location::Location(size_t pointValRange) :
    x(makeRandomPoint(pointValRange)),
    y(makeRandomPoint(pointValRange))
    {}

Location::Location(double xCoord, double yCoord, size_t unscaledRange) :
    x(makeIDFromCoord(xCoord, unscaledRange), xCoord),
    y(makeIDFromCoord(yCoord, unscaledRange), yCoord)
    {}

Location::Location(const Location &l2) : x(l2.x), y(l2.y) {}

double Location::getXCoord() const {
    return x.getCoordinate();
}

double Location::getYCoord() const {
    return y.getCoordinate();
}

bool Location::operator==(const Location &rhs) const {
    return x.getID() == rhs.x.getID() &&
           y.getID() == rhs.y.getID();
}

bool Location::operator!=(const Location &rhs) const {
    return !(rhs == *this);
}


size_t Location::getScaledPointRange(size_t unscaledRange) {
    return SCALING_FACTOR * unscaledRange;
}

Point Location::makeRandomPoint(size_t unscaledRange) {
    // the number of possible points to be sampled from
    // higher pointRange means less chance for randomly sampling duplicate points
    size_t pointRange = getScaledPointRange(unscaledRange);

    // make a number between 0 and pointRange, exclusive
    // this number is the id of the coordinate
    // (using int IDs to compare with other coordinates for duplicates)
    size_t id = rand() % pointRange;

    /*
     * turn this number into a double between -1 and 1 (coordinate range for openGL)
     * this is done the following way:
     * 1) divide id by pointRange
     *    this will give a double between 0 and 1
     * 2) multiply this new double by 2 to get a double between 0 and 2
     * 3) subtract 1 from it to get a double between -1 and 1
     */
    double pos = (((double)id / pointRange) * 2) - 1;

    return Point{id, pos};
}

/*
 * this method is the inverse transformation of madeRandomPoint()
 * (makeRandomPoint() maps an id to a coord ... this method maps a coord to an ID)
 */
size_t Location::makeIDFromCoord(double coord, size_t unscaledRange) {
    size_t pointRange = getScaledPointRange(unscaledRange);
    return (size_t) round((pointRange * (coord + 1)) / 2);
}
