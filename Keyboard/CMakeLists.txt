cmake_minimum_required(VERSION 3.27)
project(Keyboard)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_COMPILER "/usr/bin/g++-11")
#set(CMAKE_CXX_COMPILER "/usr/bin/clang++-12")
#set(CMAKE_CXX_COMPILER "/opt/intel/oneapi/compiler/2023.1.0/linux/bin/icpx")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=x86-64") # -march=native
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

# cmake -DCMAKE_BUILD_TYPE=DEBUG | RELEASE | RELWITHDEBINFO | MINSIZEREL ...
set(CMAKE_BUILD_TYPE RELEASE)
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

add_executable(Keyboard main.cpp)
