//
// Created by adlarkin on 10/31/18.
//

#include "Coordinate.h"

Coordinate::Coordinate(int id, float pos) : id(id), pos(pos) {}

bool Coordinate::operator==(const Coordinate &rhs) const {
    return id == rhs.id;
}

bool Coordinate::operator!=(const Coordinate &rhs) const {
    return !(rhs == *this);
}

int Coordinate::getId() const {
    return id;
}

void Coordinate::setId(int id) {
    Coordinate::id = id;
}

float Coordinate::getPos() const {
    return pos;
}

void Coordinate::setPos(float pos) {
    Coordinate::pos = pos;
}