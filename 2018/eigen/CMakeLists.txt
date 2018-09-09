cmake_minimum_required(VERSION 3.5)

project(eigen-start LANGUAGES CXX)

add_compile_options(-std=c++11)

INCLUDE_DIRECTORIES(~/src/vcpkg/installed/x64-linux/include/)

find_package(Eigen3 CONFIG REQUIRED 
            PATHS ~/src/vcpkg/installed/x64-linux/
			 )

add_executable(hello_world src/hello_world.cpp)

add_executable(linear src/linear.cpp)
