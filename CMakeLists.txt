cmake_minimum_required(VERSION 3.3)
project(OpenCVSpike)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES obstacle_avoidance.cpp)
add_executable(OpenCVSpike ${SOURCE_FILES})

find_package( OpenCV )
include_directories( ${OpenCV_INCLUDE_DIRS} )
target_link_libraries( OpenCVSpike ${OpenCV_LIBS} )