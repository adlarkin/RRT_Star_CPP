//
// Created by adlarkin on 10/30/18.
//

#include "Location.h"
#include <random>

#define SCALING_FACTOR 4

// makes a random location given the range of points to sample from
Location::Location(size_t unscaledPointRange) :
    x(makeRandomPoint(unscaledPointRange)),
    y(makeRandomPoint(unscaledPointRange))
    {}

// makes an already-known location given the coordinates (need the IDs)
Location::Location(double xCoord, double yCoord, size_t unscaledPointRange) :
    x(makeIDFromCoord(xCoord, unscaledPointRange), xCoord),
    y(makeIDFromCoord(yCoord, unscaledPointRange), yCoord)
    {}

// makes an already-known location given the IDs (need screen space coordinates)
Location::Location(size_t x_id, size_t y_id, size_t scaledPointRange) :
    x(x_id, makeCoordFromID(x_id, scaledPointRange)),
    y(y_id, makeCoordFromID(y_id, scaledPointRange))
    {}

Location::Location(const Location &l2) : x(l2.x), y(l2.y) {}

double Location::getXCoord() const {
    return x.getCoordinate();
}

double Location::getYCoord() const {
    return y.getCoordinate();
}

size_t Location::getX_ID() const {
    return x.getID();
}

size_t Location::getY_ID() const {
    return y.getID();
}

bool Location::operator==(const Location &rhs) const {
    return x.getID() == rhs.x.getID() &&
           y.getID() == rhs.y.getID();
}

bool Location::operator!=(const Location &rhs) const {
    return !(rhs == *this);
}


size_t Location::getScaledPointRange(size_t unscaledPointRange) {
    return SCALING_FACTOR * unscaledPointRange;
}

size_t Location::makeIDFromPointRange(size_t scaledPointRange) {
    return rand() % scaledPointRange;
}

Point Location::makeRandomPoint(size_t unscaledPointRange) {
    // the number of possible points to be sampled from
    // (higher pointRange means less chance for randomly sampling duplicate points)
    size_t pointRange = getScaledPointRange(unscaledPointRange);

    // make a number between 0 and pointRange, exclusive
    // this number is the id of the coordinate
    // (using int IDs to compare with other coordinates for duplicates)
    size_t id = Location::makeIDFromPointRange(pointRange);

    // the id now needs to be mapped to an actual screen coordinate so it can be displayed
    double pos = makeCoordFromID(id, pointRange);

    return Point{id, pos};
}

/*
 * this method is the inverse transformation of madeRandomPoint()
 * (makeRandomPoint() maps an id to a coord ... this method maps a coord to an ID)
 */
size_t Location::makeIDFromCoord(double coord, size_t unscaledPointRange) {
    size_t pointRange = getScaledPointRange(unscaledPointRange);
    return (size_t) round((pointRange * (coord + 1)) / 2);
}

double Location::makeCoordFromID(size_t id, size_t scaledPointRange) {
    /*
     * turn the id into a double between -1 and 1 (coordinate range for openGL)
     * this is done the following way:
     * 1) divide id by scaledPointRange
     *    this will give a double between 0 and 1
     * 2) multiply this new double by 2 to get a double between 0 and 2
     * 3) subtract 1 from it to get a double between -1 and 1
     */
    return (((double)id / scaledPointRange) * 2) - 1;
}
