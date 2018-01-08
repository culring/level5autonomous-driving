cmake_minimum_required(VERSION 3.9)   # CMake version check
project(level5autonomous-driving)               # Create project "simple_example"
set(CMAKE_CXX_STANDARD 14)            # Enable c++11 standard

set(SOURCE_FILES main.cpp Model.cpp View/ViewCar.cpp View/ViewTrack.cpp View/ViewTrack.h View/ViewSegment.cpp View/ViewSegment.h View/ViewCamera.cpp View/ViewCamera.h View/View.cpp View/View.h)            # Add main.cpp file of project root directory as source file
add_executable(level5autonomous-driving ${SOURCE_FILES})       # Add executable target with source files listed in SOURCE_FILES variable