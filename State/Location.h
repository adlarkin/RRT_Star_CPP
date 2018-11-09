//
// Created by adlarkin on 10/30/18.
//

#ifndef RRT_PROJECT_LOCATION_H
#define RRT_PROJECT_LOCATION_H


#include <queue>

// needed for the rTree
//#include <boost/geometry/geometries/BoostPoint.hpp>
#include <boost/geometry.hpp>
typedef boost::geometry::model::point<float, 2, boost::geometry::cs::cartesian> BoostPoint;

class Location {
public:
    Location(float x_coord, float y_coord);
    float getXCoord() const;
    float getYCoord() const;
    void changeCoords(float x, float y);
    BoostPoint getBoostPoint();  // needed for the rTree

    bool operator==(const Location &rhs) const;
    bool operator!=(const Location &rhs) const;
private:
    float xCoord;
    float yCoord;
};

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