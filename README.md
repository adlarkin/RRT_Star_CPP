# RRT_Star_CPP
RRT* Planner for distance or (hopefully) energy efficiency (C++)

Make sure you have openGL installed ... instructions here:
- http://www.codebind.com/linux-tutorials/install-opengl-ubuntu-linux/
(this project uses freeGlut to actually implement openGL, not glut)

Next, if using CLion, you need to add the following to your CMakeLists.txt file:
- target_link_libraries(PROJECT_NAME -lglut -lGL -lGLU)
- when adding the above line, replace 'PROJECT_NAME' with the name of your project

In order to use the rTree data structure, ensure that boost is installed:
- https://www.boost.org/doc/libs/1_68_0/more/getting_started/index.html
- https://www.boost.org/doc/libs/1_69_0/more/getting_started/unix-variants.html

To run the program, you must pass in command-line parameters. The parameter list is as follows:
- executable x_winPos y_winPos winWidth winHeight numPoints epsilon plannerType neighborhoodSize knnNeighborhoodRadiusFactor testSeed
- 'plannerType' should be either "distance" or "energy" (it is NOT case sensitive)
- 'knnNeighborhoodRadiusFactor' determines how big of a search radius is used when looking for solutions and states to rewire
    - for example, if you set this to 1.5, then you will search for states within 1.5*epsilon
    - when looking for solutions, the planner will take the best state within this search radius from the goal state (if one exists)
- the 'testSeed' parameter is optional


More info on rTree can be found here:
- https://www.boost.org/doc/libs/1_68_0/libs/geometry/doc/html/geometry/spatial_indexes/introduction.html

Using double buffer for the drawer (openGL-based) because of dedicated graphics cards:
- https://stackoverflow.com/questions/18816882/no-display-transparent-window-with-opengl-2-and-primusrun-on-single-buffer
- https://stackoverflow.com/questions/28298540/difference-between-single-bufferedglut-single-and-double-buffered-drawingglut
