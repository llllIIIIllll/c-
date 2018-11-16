cmake_minimum_required(VERSION 3.5)

project(ceres-start LANGUAGES CXX)

add_compile_options(-std=c++11)
find_package(Ceres REQUIRED)

include_directories(
  include
  ${EIGEN3_INCLUDE_DIR}
  ${CERES_INCLUDE_DIRS}
)

add_executable(hello hello.cpp)
target_link_libraries(hello ceres)
