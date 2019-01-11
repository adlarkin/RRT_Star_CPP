//
// Created by adlarkin on 1/11/19.
//

#ifndef RRT_STAR_CPP_OBSTACLES_H
#define RRT_STAR_CPP_OBSTACLES_H


#include <cstddef>

class Obstacles {
public:
    Obstacles(size_t dimension, size_t numOfObstacles);
    virtual ~Obstacles();

private:
    void initObstacleArray();
    void makeRandomObstacles(size_t numOfObstacles);
    void destroyObstacleArray();

    size_t arrayDim;

    // a 2D array of booleans, of size arrayDim x arrayDim
    // indexing an array is like indexing a location through the ID
    // ex: obstacleLocations[1][2] will return if there's an object at (1,2)
    bool **obstacleLocations;
};


#endif //RRT_STAR_CPP_OBSTACLES_H
