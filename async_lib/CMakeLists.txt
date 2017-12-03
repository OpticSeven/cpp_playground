cmake_minimum_required( VERSION 3.1)

project(asyncN)

find_package (Threads)

add_executable(asyncN ${PROJECT_SOURCE_DIR}/src/main.cpp 
  ${PROJECT_SOURCE_DIR}/src/async.cpp)

if(NOT CMAKE_DEBUG_POSTFIX)
  set(CMAKE_DEBUG_POSTFIX d)
endif()

target_link_libraries (asyncN ${CMAKE_THREAD_LIBS_INIT})

set_target_properties(asyncN PROPERTIES
   CXX_STANDARD 11
   CXX_STANDARD_REQUIRED ON
   CXX_EXTENSIONS OFF
)

