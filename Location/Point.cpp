//
// Created by adlarkin on 11/16/18.
//

#include "Point.h"

Point::Point(size_t ID, double coordinate) : ID(ID), coordinate(coordinate) {}

Point::Point(const Point &p2) : ID(p2.ID), coordinate(p2.coordinate) {}

size_t Point::getID() const {
    return ID;
}

void Point::setID(size_t ID) {
    Point::ID = ID;
}

double Point::getCoordinate() const {
    return coordinate;
}

void Point::setCoordinate(double coordinate) {
    Point::coordinate = coordinate;
}
