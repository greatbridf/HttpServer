cmake_minimum_required(VERSION 3.15)
project(CoreHandlers)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-O3 ${CMAKE_CXX_FLAGS}")

include_directories(.)

add_library(GetHandler SHARED
        GetHandler.hpp
        GetHandler.cpp)
add_library(PostHandler SHARED
        PostHandler.hpp
        PostHandler.cpp)
add_library(PlainTextHandler SHARED
        PlainText.hpp
        PlainText.cpp
)
target_link_libraries(GetHandler HttpParser_Core)
target_link_libraries(PostHandler HttpParser_Core)
target_link_libraries(PlainTextHandler HttpParser_Core)
