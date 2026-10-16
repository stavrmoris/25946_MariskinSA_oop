cmake_minimum_required(VERSION 3.14)
project(oop05_task_5 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
if(MSVC)
    add_compile_options(/utf-8 /W4)
else()
    add_compile_options(-Wall -Wextra -pedantic)
endif()

add_subdirectory(lib)

add_executable(average_app main.cpp)
target_link_libraries(average_app PRIVATE average)

option(BUILD_TESTS "собирать тесты библиотеки" ON)
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
