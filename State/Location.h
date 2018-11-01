//
// Created by adlarkin on 10/30/18.
//

#ifndef RRT_PROJECT_LOCATION_H
#define RRT_PROJECT_LOCATION_H


#include "Coordinate.h"

class Location {
public:
    Location(const Coordinate &x_coord, const Coordinate &y_coord);

    bool operator==(const Location &rhs) const;
    bool operator!=(const Location &rhs) const;

    float xPosition();
    float yPosition();

    int xID();
    int yID();

private:
    Coordinate x_coord;
    Coordinate y_coord;
};


#endif //RRT_PROJECT_LOCATION_H