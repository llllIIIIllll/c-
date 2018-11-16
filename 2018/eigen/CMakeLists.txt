cmake_minimum_required(VERSION 3.5)

project(eigen-start LANGUAGES CXX)

add_compile_options(-std=c++11)
find_package(Eigen3 REQUIRED)

INCLUDE_DIRECTORIES(/usr/local/include/eigen3/
${EIGEN3_INCLUDE_DIR}
)

add_executable(hello_world src/hello_world.cpp)
add_executable(linear src/linear.cpp)
add_executable(eigen_types src/eigen_types.cpp)
add_executable(generic src/generic.cpp)

add_executable(zero src/zero.cpp)

add_executable(rotate src/rotate.cpp)
