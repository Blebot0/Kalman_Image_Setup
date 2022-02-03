cmake_minimum_required(VERSION 3.0.2)
project(kalman_implementation)

add_compile_options(-std=c++14)

find_package(catkin REQUIRED COMPONENTS
  roscpp
)

find_package(gazebo REQUIRED)
find_package(OpenCV REQUIRED)
find_package(Eigen3 REQUIRED)

ADD_DEFINITIONS(-DCV__ENABLE_C_API_CTORS)
set(APPEND CMAKE_PREFIX_PATH "/usr/share/gazebo-10")



include_directories(
	include
  	${catkin_INCLUDE_DIRS}
	${PROJECT_SOURCE_DIR}/src
	${PROJECT_SOURCE_DIR}/include/kalman_implementation)

add_library ( Kalman_Header
	include/kalman_implementation/Kalman.hpp
	src/Kalman.cpp
	)

link_directories(${GAZEBO_LIBRARY_DIRS})
list(APPEND CMAKE_CXX_FLAGS "${GAZEBO_CXX_FLAGS}")


include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(gazebo_fetch_camera src/gazebo_fetch_camera.cpp)

target_link_libraries(gazebo_fetch_camera Kalman_Header Eigen3::Eigen ${GAZEBO_LIBRARIES} ${OpenCV_LIBS} pthread)
