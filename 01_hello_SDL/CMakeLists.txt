# Minimum required CMake version
cmake_minimum_required(VERSION 3.10)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
# Project name
project(Churro_Adventures CXX)

# Specify the source directory
set(SOURCE_DIR ./)

# Collect all source files from the source directory
file(GLOB SOURCES "${SOURCE_DIR}/*.cpp")

# Add the executable target
# The second argument is the list of all source files
add_executable(Churro_Adventures ${SOURCES})
find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)
find_package(SDL3_mixer REQUIRED)

# Specify include directories so the compiler can find header files
target_link_libraries(Churro_Adventures PRIVATE SDL3::SDL3 SDL3_image::SDL3_image SDL3_mixer::SDL3_mixer)
