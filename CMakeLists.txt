# CMakeLists for the temp analysis repository

# Set up
cmake_minimum_required (VERSION 2.6)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules")

# ROOT
find_package(ROOT REQUIRED)

# Project name
project (BAND-LASER)

set(INCLUDES ${ROOT_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/include)
include_directories(${INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

# Add executable for making his
add_executable(laser_boi LASER_his.cpp)
target_link_libraries(laser_boi ${ROOT_LIBRARIES})
