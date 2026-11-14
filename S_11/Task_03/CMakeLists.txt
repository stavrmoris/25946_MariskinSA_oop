cmake_minimum_required(VERSION 3.14)
project(oop11_homework LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
if(MSVC)
    add_compile_options(/utf-8 /W4)
else()
    add_compile_options(-Wall -Wextra -pedantic)
endif()
add_library(robot STATIC robot.cpp)
target_include_directories(robot PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
add_executable(robot_app main.cpp)
target_link_libraries(robot_app PRIVATE robot)

find_program(GRAPHVIZ_DOT dot)
if(GRAPHVIZ_DOT)
    add_custom_target(uml
        COMMAND "${GRAPHVIZ_DOT}" -Tsvg "${CMAKE_CURRENT_SOURCE_DIR}/classes.dot"
                -o "${CMAKE_CURRENT_BINARY_DIR}/classes.svg"
        COMMAND "${GRAPHVIZ_DOT}" -Tpng "${CMAKE_CURRENT_SOURCE_DIR}/classes.dot"
                -o "${CMAKE_CURRENT_BINARY_DIR}/classes.png"
        COMMENT "Построение UML диаграммы роботов"
        VERBATIM)
endif()
