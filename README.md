# RRT_Star_CPP
This repository simulates the RRT* planning algorithm. A random environment is generated, along with a random start and goal location. The building of the search tree is simulated as new locations are sampled, and the path is modified over time along with outputs of the improved path cost. Currently, the heuristic used is euclidean distance. An energy metric may be incorporated later.

## Installation and Setup
This project uses openGL and C++ Boost libraries.

To install openGL (this project uses freeGlut to actually implement openGL, not glut):
```bash	
$ sudo apt update
$ sudo apt install libglu1-mesa-dev freeglut3-dev mesa-common-dev
```
To install Boost:
```bash
$ sudo apt update
$ sudo apt install libboost-dev
```

## Usage
This project uses cmake:
```bash
$ cd <PATH TO RRT_STAR_CPP DIRECTORY>
$ mkdir build
$ cd build
$ cmake ..
$ make
$ ./RRT_Star_CPP <x_winPos> <y_winPos> <winWidth> <winHeight> <numPoints> <epsilon> <plannerType> <neighborhoodSize> <knnNeighborhoodRadiusFactor> [testSeed]
```
The parameters listed above are described below. If you are unsure what to enter for the above parameters, here is an example that can be modified to your needs (it is likely that you will need to modify the window parameters to meet your screen specs):
```bash
$ ./RRT_Star_CPP 430 50 1000 900 100000 .01 distance 25 1.75
```
- x_winPos & y_winPos: defines the top-left position of the animation window  
- winWidth: the width of the animation window
- winHeight: the height of the animation window
- numPoints: the number of obstacle-free points to be sampled (# of iterations)
- epsilon: the amount the tree can expand at each iteration
- 'plannerType' should be either "distance" or "energy" (it is NOT case sensitive)
- neighborhoodSize
- 'knnNeighborhoodRadiusFactor' determines how big of a search radius is used when looking for solutions and states to rewire
    - for example, if you set this to 1.5, then you will search for states within 1.5*epsilon
    - when looking for solutions, the planner will take the best state within this search radius from the goal state (if one exists)
- testSeed: can be used for debugging
    - if nothing is listed for this parameter, a random seed is chosen
    - the seed chosen is the first line of output from the program

## Other Information
This project was implemented with C++.

More info on rTree can be found here:
- https://www.boost.org/doc/libs/1_68_0/libs/geometry/doc/html/geometry/spatial_indexes/introduction.html

Use a double buffer implementation for the drawer (updateScreen() method in Visualization/Drawer.cpp) if you have a dedicated graphics card (if not, single buffer should be used -- single buffer is the default setting in the repository):
- https://stackoverflow.com/questions/18816882/no-display-transparent-window-with-opengl-2-and-primusrun-on-single-buffer
- https://stackoverflow.com/questions/28298540/difference-between-single-bufferedglut-single-and-double-buffered-drawingglut
