cmake_minimum_required(VERSION 3.5)

project(particles)
set(EXEC_NAME "test")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

find_package(Eigen3 REQUIRED)

set(SOURCES 
    src/window.cpp 
    include/window.h

    include/entity.h
    src/entity.cpp

    src/rect.cpp
    include/rect.h

    src/physics.cpp
    include/physics.h
)

set(CMAKE_CXX_COMPILER "g++")


# add_compile_options(-O3 -Wall -Wextra -Wpedantic)
add_compile_options(-Wall -Wextra -Wpedantic)

include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/src
)

add_executable(
  ${EXEC_NAME} 
  ${SOURCES}
  src/main.cpp
)

target_link_libraries(
    ${EXEC_NAME} 
    ${SDL2_LIBRARIES}
)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
