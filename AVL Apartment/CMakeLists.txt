cmake_minimum_required(VERSION 3.20)
project(ex6_evyataralcalay)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(ex6_evyataralcalay
        Apartment.cpp
        AVL.cpp
        Stack.cpp
        new_presubmit.cpp
        #test_runner.cpp
        #tests.cpp
        )
