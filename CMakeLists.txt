cmake_minimum_required(VERSION 2.8.3)
project(lab1)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  geometry_msgs
  gazebo_ros
)

catkin_package(
DEPENDS gazebo_ros
)


include_directories(
${catkin_INCLUDE_DIRS}
${GAZEBO_INCLUDE_DIRS}
${SDFormat_INCLUDE_DIRS}
)

add_executable(lab1 rope.h generatesdf.cpp newRope.cpp)

target_link_libraries(lab1 ${catkin_LIBRARIES})

