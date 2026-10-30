cmake_minimum_required(VERSION 3.14)
project(oop07_task_6 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
if(MSVC)
    add_compile_options(/utf-8 /W4)
else()
    add_compile_options(-Wall -Wextra -pedantic)
endif()

add_library(robot INTERFACE)
target_include_directories(robot INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(robot_app main.cpp)
target_link_libraries(robot_app PRIVATE robot)

add_executable(robot_lifetime main_lifetime.cpp)
target_link_libraries(robot_lifetime PRIVATE robot)

add_executable(robot_containers main_containers.cpp)
target_link_libraries(robot_containers PRIVATE robot)
