//
// Created by adlarkin on 1/11/19.
//

#include <iostream>
#include "Obstacles.h"

Obstacles::Obstacles(size_t dimension, size_t numOfObstacles) : arrayDim(dimension) {
    initObstacleArray();
    makeRandomObstacles(numOfObstacles);
}

Obstacles::~Obstacles() {
    destroyObstacleArray();
}

void Obstacles::initObstacleArray() {
    std::cout << "starting the obstacle initialization..." << std::endl;
    std::cout << "arrayDim is " << arrayDim << std::endl;
    obstacleLocations = new bool*[arrayDim];
    for (size_t i = 0; i < arrayDim; ++i) {
        obstacleLocations[i] = new bool[arrayDim];
    }
    std::cout << "made it to middle" << std::endl;
    // set all values in the array to false
    for (size_t x = 0; x < arrayDim; ++x) {
        for (size_t y = 0; y < arrayDim; ++y) {
            obstacleLocations[x][y] = false;
        }
    }
    std::cout << "done" << std::endl;
}

void Obstacles::makeRandomObstacles(size_t numOfObstacles) {
    // todo fill this in
}

void Obstacles::destroyObstacleArray() {
    for(size_t i = 0; i < arrayDim; ++i)
        delete [] obstacleLocations[i];
    delete [] obstacleLocations;
}
