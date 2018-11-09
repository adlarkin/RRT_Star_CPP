//
// Created by adlarkin on 10/30/18.
//

#include "Location.h"

Location::Location(float x_coord, float y_coord) : xCoord(x_coord), yCoord(y_coord) {}

float Location::getXCoord() const {
    return xCoord;
}

float Location::getYCoord() const {
    return yCoord;
}

void Location::changeCoords(float x, float y) {
    this->xCoord = x;
    this->yCoord = y;
}

BoostPoint Location::getBoostPoint() {
    return BoostPoint{xCoord, yCoord};
}

bool Location::operator==(const Location &rhs) const {
    return xCoord == rhs.xCoord &&
           yCoord == rhs.yCoord;
}

bool Location::operator!=(const Location &rhs) const {
    return !(rhs == *this);
}
