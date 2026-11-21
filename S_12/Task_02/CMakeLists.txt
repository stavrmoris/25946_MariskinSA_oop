cmake_minimum_required(VERSION 3.14)
project(oop12_homework LANGUAGES CXX)
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

find_package(Doxygen QUIET COMPONENTS dot)
if(DOXYGEN_FOUND)
    configure_file(Doxyfile.in Doxyfile @ONLY)
    add_custom_target(docs
        COMMAND "${DOXYGEN_EXECUTABLE}" "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile"
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
        COMMENT "Генерация документации и диаграмм иерархии роботов"
        VERBATIM)
else()
    message(STATUS "Для цели docs нужны Doxygen и Graphviz")
endif()
