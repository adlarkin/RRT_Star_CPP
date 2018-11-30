//
// Created by adlarkin on 11/16/18.
//

#include "Point.h"

Point::Point(int ID, float coordinate) : ID(ID), coordinate(coordinate) {}

Point::Point(const Point &p2) : ID(p2.ID), coordinate(p2.coordinate) {}

int Point::getID() const {
    return ID;
}

void Point::setID(int ID) {
    Point::ID = ID;
}

float Point::getCoordinate() const {
    return coordinate;
}

void Point::setCoordinate(float coordinate) {
    Point::coordinate = coordinate;
}
