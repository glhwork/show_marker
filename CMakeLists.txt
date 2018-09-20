cmake_minimum_required(VERSION 2.8.3)
project(show_marker)


find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  nav_msgs
  roscpp
  rospy
  std_msgs
)


catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES localization_marker
#  CATKIN_DEPENDS geometry_msgs nav_msgs roscpp rospy std_msgs
#  DEPENDS system_lib
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_executable(localization_marker
  src/localization_marker.cpp
)
target_link_libraries(localization_marker
  ${catkin_LIBRARIES}
)

