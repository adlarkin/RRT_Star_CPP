//
// Created by adlarkin on 10/30/18.
//

#ifndef RRT_PROJECT_LOCATION_H
#define RRT_PROJECT_LOCATION_H


#include <queue>
#include "Point.h"

class Location {
public:
    explicit Location(size_t unscaledPointRange);
    Location(double xCoord, double yCoord, size_t unscaledPointRange);
    Location(size_t x_id, size_t y_id, size_t scaledPointRange);
    Location(const Location &l2);

    double getXCoord() const;
    double getYCoord() const;
    size_t getX_ID() const;
    size_t getY_ID() const;

    bool operator==(const Location &rhs) const;
    bool operator!=(const Location &rhs) const;

    // useful to have these as public static methods if you want to make obstacles
    // (assuming obstacle hashing is being used)
    static size_t getScaledPointRange(size_t unscaledPointRange);
    static size_t makeIDFromPointRange(size_t scaledPointRange);

private:
    Point makeRandomPoint(size_t unscaledPointRange);
    size_t makeIDFromCoord(double coord, size_t unscaledPointRange);
    double makeCoordFromID(size_t id, size_t scaledPointRange);

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