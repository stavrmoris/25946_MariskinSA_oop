add_library(average STATIC average.cpp average.h)
target_include_directories(average PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
