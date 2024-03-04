cmake_minimum_required(VERSION 3.10)
project(S2_Robotics)

# Add executable target with source files
add_executable(Output source-code/main.cpp source-code/robotics.cpp)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
