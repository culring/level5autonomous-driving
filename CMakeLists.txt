cmake_minimum_required(VERSION 3.9)   # CMake version check
project(level5autonomous-driving)               # Create project "simple_example"
set(CMAKE_CXX_STANDARD 14)            # Enable c++11 standard

set(SOURCE_FILES main.cpp Model.cpp View/ViewCar.cpp View/ViewTrack.cpp View/ViewSegment.cpp View/ViewCamera.cpp View/View.cpp)            # Add main.cpp file of project root directory as source file
add_executable(level5autonomous-driving ${SOURCE_FILES})       # Add executable target with source files listed in SOURCE_FILES variable

# Detect and add SFML
set(SFML_ROOT "SFML")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIRS})
    set(LIBS $(LIBS) $(SFML_LIBRARIES))
    target_link_libraries(level5autonomous-driving $(LIBS))
endif(SFML_FOUND)