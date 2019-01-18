//
// Created by adlarkin on 11/16/18.
//

#ifndef RRT_STAR_CPP_POINT_H
#define RRT_STAR_CPP_POINT_H

#include <cstddef>

class Point {
public:
    Point(size_t ID, double coordinate);
    Point(const Point &p2);

    size_t getID() const;

    void setID(size_t ID);

    double getCoordinate() const;

    void setCoordinate(double coordinate);

private:
    size_t ID; // for obstacle hashing
    double coordinate;
};


#endif //RRT_STAR_CPP_POINT_H
