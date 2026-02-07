# Minimum required CMake version
cmake_minimum_required(VERSION 3.10)

# Project name
project(Churro_Adventures CXX)

# Specify the source directory
set(SOURCE_DIR ./)

# Collect all source files from the source directory
file(GLOB SOURCES "${SOURCE_DIR}/*.cpp" "${SOURCE_DIR}/*.h")

# Add the executable target
# The second argument is the list of all source files
add_executable(Churro_Adventures ${SOURCES})

# Specify include directories so the compiler can find header files
target_include_directories(Churro_Adventures PRIVATE SDL3::SDL3 SDL3::SDL3_image)
