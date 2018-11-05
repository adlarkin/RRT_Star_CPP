# RRT_Star_CPP
RRT* Planner for distance or (hopefully) energy efficiency (C++)

Make sure you have openGL installed ... instructions here: 
- http://www.codebind.com/linux-tutorials/install-opengl-ubuntu-linux/

Next, if using CLion, you need to add the following to your CMakeLists.txt file:
- target_link_libraries(PROJECT_NAME -lglut -lGL -lGLU)
- when adding the above line, replace 'PROJECT_NAME' with the name of your project

In order to use rTree (in Planner/Planner.h), ensure that boost is installed:
- https://www.boost.org/doc/libs/1_68_0/more/getting_started/index.html
More info on rTree can be found here:
- https://www.boost.org/doc/libs/1_68_0/libs/geometry/doc/html/geometry/spatial_indexes/introduction.html
