//
// Created by adlarkin on 1/14/19.
//

#ifndef RRT_STAR_CPP_DISPLAYABLERECTOBSTACLE_H
#define RRT_STAR_CPP_DISPLAYABLERECTOBSTACLE_H


#include <cstddef>
#include "../Location/Location.h"

class DisplayableRectObstacle {
public:
    explicit DisplayableRectObstacle(size_t scaledPointRange);
    Location getTopLeftLoc() const;

    size_t getX_min() const;
    size_t getX_max() const;
    size_t getY_min() const;
    size_t getY_max() const;

private:
    size_t scaledPointRange;
    size_t x_min;
    size_t x_max;
    size_t y_min;
    size_t y_max;
};


#endif //RRT_STAR_CPP_DISPLAYABLERECTOBSTACLE_H
