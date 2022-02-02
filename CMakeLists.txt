cmake_minimum_required(VERSION 3.0.2)
project(kalman_implementation)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
)

find_package(gazebo REQUIRED)
find_package(OpenCV REQUIRED)
find_package(Eigen3 REQUIRED)
ADD_DEFINITIONS(-DCV__ENABLE_C_API_CTORS)
## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)

set(APPEND CMAKE_PREFIX_PATH "/usr/share/gazebo-10")

link_directories(${GAZEBO_LIBRARY_DIRS})
list(APPEND CMAKE_CXX_FLAGS "${GAZEBO_CXX_FLAGS}")

include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(gazebo_fetch_camera src/gazebo_fetch_camera.cpp)
target_link_libraries(gazebo_fetch_camera Eigen3::Eigen ${GAZEBO_LIBRARIES} ${OpenCV_LIBS} pthread)
include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)
