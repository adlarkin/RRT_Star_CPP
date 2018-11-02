//
// Created by adlarkin on 10/30/18.
//

#ifndef RRT_PROJECT_LOCATION_H
#define RRT_PROJECT_LOCATION_H


#include <queue>
#include "Coordinate.h"

class Location {
public:
    Location(const Coordinate &x_coord, const Coordinate &y_coord);

    bool operator==(const Location &rhs) const;
    bool operator!=(const Location &rhs) const;

    float xPosition() const;
    float yPosition() const;

    int xID() const;
    int yID() const;

private:
    Coordinate x_coord;
    Coordinate y_coord;
};


#endif //RRT_PROJECT_LOCATION_H