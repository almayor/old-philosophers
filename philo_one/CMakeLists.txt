cmake_minimum_required(VERSION 3.19)
project(philo_one C)

set(CMAKE_C_STANDARD 11)

include_directories(include)

add_executable(philo_one
        include/philo_one.h
        src/main.c
        src/utils.c src/philosopher.c src/chrono.c src/aff.c src/routine.c src/clean_exit.c)

target_link_libraries(philo_one -lpthread)