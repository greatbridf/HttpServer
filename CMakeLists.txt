cmake_minimum_required(VERSION 3.15)
project(HttpParser)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-O3 -fPIC ${CMAKE_CXX_FLAGS}")

include_directories(.)
include_directories(HttpParser_Core/include)

add_executable(HttpParser Application.cpp main.cpp src/RequestHandler.cpp)
target_link_libraries(HttpParser HttpParser_Core pthread dl)

# plugins

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/plugins/)

add_subdirectory(HttpParser_Core)
add_subdirectory(Handler/Base)
add_subdirectory(Test)
