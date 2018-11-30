//
// Created by adlarkin on 10/30/18.
//

#ifndef RRT_PROJECT_LOCATION_H
#define RRT_PROJECT_LOCATION_H


#include <queue>
#include "Point.h"

// needed for the rTree
//#include <boost/geometry/geometries/BoostPoint.hpp>
#include <boost/geometry.hpp>

typedef boost::geometry::model::point<float, 2, boost::geometry::cs::cartesian> BoostPoint;

class Location {
public:
    explicit Location(int pointValRange);
    Location(const Location &l2);

    float getXCoord() const;
    float getYCoord() const;

    BoostPoint getBoostPoint();  // needed for the rTree

    bool operator==(const Location &rhs) const;
    bool operator!=(const Location &rhs) const;

private:
    static Point makeRandomPoint(int pointValRange);

    Point x;
    Point y;
};

// for use in unordered set (if you want to check for duplicate locations ... it may not matter)
namespace std {
    template<>
    struct hash<Location> {
        size_t operator()(const Location &obj) const {
            size_t h1 = hash<float>()(obj.getXCoord());
            size_t h2 = hash<float >()(obj.getYCoord());
            return h1 ^ (h2 << 1);
        }
    };
}

#endif //RRT_PROJECT_LOCATION_H