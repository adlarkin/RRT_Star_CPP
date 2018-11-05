cmake_minimum_required(VERSION 3.12)
project(RRT_Star_CPP)

set(CMAKE_CXX_STANDARD 14)

add_executable(RRT_Star_CPP main.cpp Planner/Planner.cpp Planner/Planner.h
        State/Location.cpp State/Location.h State/Coordinate.cpp State/Coordinate.h
        State/RobotState.cpp State/RobotState.h Utils/ObjHashes.cpp Visualization/ShapeDrawer.cpp Visualization/ShapeDrawer.h)

# added this in so that openGL works with the project
target_link_libraries(RRT_Star_CPP -lglut -lGL -lGLU)