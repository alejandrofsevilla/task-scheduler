cmake_minimum_required(VERSION 3.22.0)

project(task-scheduler LANGUAGES CXX)

add_subdirectory(example)

add_library(task-scheduler SHARED
  Task.hpp
  TaskScheduler.hpp
  TaskScheduler.cpp)

target_compile_features(task-scheduler PRIVATE cxx_std_17)
target_compile_options(task-scheduler PRIVATE -Wall -Wextra -Wpedantic -Werror -O0)

