cmake_minimum_required(VERSION 3.12)
project(RRT_Star_CPP)

set(CMAKE_CXX_STANDARD 14)

add_executable(RRT_Star_CPP main.cpp
        Planner/Planner.cpp Planner/Planner.h
        Location/Location.cpp Location/Location.h
        State/RobotState.cpp State/RobotState.h
        Visualization/Drawer.cpp Visualization/Drawer.h
        Utils/MyRtree.cpp Utils/MyRtree.h
        Location/Point.cpp Location/Point.h
        Planner/DistancePlanner.cpp Planner/DistancePlanner.h
        Planner/EnergyPlanner.cpp Planner/EnergyPlanner.h
        Visualization/WindowParamsDTO.cpp Visualization/WindowParamsDTO.h
        Utils/StringParser.cpp Utils/StringParser.h
        Obstacle/Obstacles.cpp Obstacle/Obstacles.h
        Obstacle/DisplayableRectObstacle.cpp Obstacle/DisplayableRectObstacle.h)

# added this in so that openGL works with the project
target_link_libraries(RRT_Star_CPP -lglut -lGL -lGLU)