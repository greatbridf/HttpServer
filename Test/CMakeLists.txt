cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-O3 -fPIC ${CMAKE_CXX_FLAGS}")

include_directories(.)

add_executable(TestPlayground main.cpp)
target_link_libraries(TestPlayground HttpParser_Core pthread dl)
