cmake_minimum_required(VERSION 3.15)
project(CoreHandlers)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-O3 ${CMAKE_CXX_FLAGS}")

include_directories(.)

add_library(GetHandler SHARED
        GetHandler.hpp
        GetHandler.cpp)
target_link_libraries(GetHandler HttpParser_Core)
file(MAKE_DIRECTORY ${PROJECT_SOURCE_DIR}/../../cmake-build-debug/plugins/)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../../cmake-build-debug/plugins/)
