//
// Created by adlarkin on 1/11/19.
//

#ifndef RRT_STAR_CPP_OBSTACLES_H
#define RRT_STAR_CPP_OBSTACLES_H


#include <cstddef>
#include <vector>

struct rectangularObstacle {
    size_t x_Min;
    size_t x_Max;
    size_t y_Min;
    size_t y_Max;
};

class Obstacles {
public:
    Obstacles(size_t scaledPointRange, size_t numOfObstacles);

private:
    void makeRandomObstacles(size_t numOfObstacles);

    std::vector<rectangularObstacle> existingObstacles;
};


#endif //RRT_STAR_CPP_OBSTACLES_H
