cmake_minimum_required( VERSION 3.1)

project(asyncN)

add_executable(asyncN main.cpp)

set_target_properties(asyncN PROPERTIES
   CXX_STANDARD 11
   CXX_STANDARD_REQUIRED ON
   CXX_EXTENSIONS OFF
)
