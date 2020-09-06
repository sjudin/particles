cmake_minimum_required(VERSION 3.5)

project(particles)
set(EXEC_NAME "test")

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
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


add_compile_options(-Wall -Wextra -Wpedantic)

include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/src
    D:/cpp_projects/Development/SDL2_MinGW_32Bit/include/SDL2
    D:/cpp_projects/Development/eigen
)

add_executable(
  ${EXEC_NAME} 
  ${SOURCES}
  src/main.cpp
)

target_link_libraries(
    ${EXEC_NAME} 
    mingw32
    D:/cpp_projects/Development/SDL2_MinGW_32Bit/lib/libSDL2main.a
    D:/cpp_projects/Development/SDL2_MinGW_32Bit/bin/SDL2.dll
)

target_include_directories(
    ${EXEC_NAME} 
    PRIVATE 
    D:/cpp_projects/Development/SDL2_MinGW_32Bit/include
    D:/cpp_projects/Development/eigen 
)
