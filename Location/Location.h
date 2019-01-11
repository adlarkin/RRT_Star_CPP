//
// Created by adlarkin on 10/30/18.
//

#ifndef RRT_PROJECT_LOCATION_H
#define RRT_PROJECT_LOCATION_H


#include <queue>
#include "Point.h"

class Location {
public:
    explicit Location(size_t pointValRange);
    Location(double xCoord, double yCoord, size_t unscaledRange);
    Location(const Location &l2);

    double getXCoord() const;
    double getYCoord() const;

    bool operator==(const Location &rhs) const;
    bool operator!=(const Location &rhs) const;

    // useful to have this is a public static method if you want to make obstacles
    // (assuming obstacle hashing is being used)
    static size_t getScaledPointRange(size_t unscaledRange);

private:
    Point makeRandomPoint(size_t unscaledRange);
    size_t makeIDFromCoord(double coord, size_t unscaledRange);

    Point x;
    Point y;
};

// hashcode (for use in unordered set)
// this is needed if you want to check for duplicate locations
namespace std {
    template<>
    struct hash<Location> {
        size_t operator()(const Location &obj) const {
            size_t h1 = hash<double>()(obj.getXCoord());
            size_t h2 = hash<double>()(obj.getYCoord());
            return h1 ^ (h2 << 1);
        }
    };
}

#endif //RRT_PROJECT_LOCATION_H