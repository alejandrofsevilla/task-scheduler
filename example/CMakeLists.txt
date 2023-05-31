add_executable(task-scheduler-example main.cpp)
target_compile_features(task-scheduler-example PUBLIC cxx_std_17)
target_link_libraries(task-scheduler-example PRIVATE task-scheduler)
target_include_directories(task-scheduler-example PUBLIC ..)
