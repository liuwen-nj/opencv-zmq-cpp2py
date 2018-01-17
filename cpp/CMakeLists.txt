project(cpp-python-cvmat-pipe)

cmake_minimum_required(VERSION 3.0.2 FATAL_ERROR)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set (CMAKE_CXX_FLAHS "${CMAKE_CXX_FLAGS} -march=native")
set (CMAKE_BUILD_TYPE Debug)

find_package (OpenCV REQUIRED)
#find_package (OpenCV 3.0 REQUIRED)

find_package(cppzmq)
include_directories(${cppzmq_INCLUDE_DIR})

add_executable(pub src/pub.cpp)
target_link_libraries(pub ${OpenCV_LIBS} ${cppzmq_LIBRARY})