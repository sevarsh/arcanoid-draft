cmake_minimum_required(VERSION 3.21)  # CMake version check
project(arcanoid)                     # Create project
set(CMAKE_CXX_STANDARD 11)            # Enable c++11 standard

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)

# Suppress warnings of the deprecation of glut functions on macOS. 
if(APPLE)
    add_definitions(-Wno-deprecated-declarations) 
endif()

# Add header files
include_directories("headers/")

# Add source directory
aux_source_directory("src/" SRC_DIR)

# Set source files
set(SOURCE_FILES main.cpp ${SRC_DIR})

# Find packages
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories(${OPENGL_INCLUDE_DIR} ${GLUT_INCLUDE_DIR})

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(arcanoid ${SOURCE_FILES} ${HEADER_FILES})

# Link libraries
target_link_libraries(arcanoid ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})#GLUT::GLUT)


