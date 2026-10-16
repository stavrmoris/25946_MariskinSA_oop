add_library(average INTERFACE)
target_include_directories(average INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")
target_compile_features(average INTERFACE cxx_std_17)
