cmake_minimum_required(VERSION 3.15)
project(Servlet)

set(CMAKE_CXX_STANDARD 17)
if (CMAKE_BUILD_TYPE STREQUAL Debug)
    set(CMAKE_CXX_FLAGS "-g -fPIC ${CMAKE_CXX_FLAGS}")
elseif (CMAKE_BUILD_TYPE STREQUAL Release)
    set(CMAKE_CXX_FLAGS "-O3 -fPIC ${CMAKE_CXX_FLAGS}")
elseif (CMAKE_BUILD_TYPE STREQUAL RelWithDebInfo)
    set(CMAKE_CXX_FLAGS "-g -O3 -fPIC ${CMAKE_CXX_FLAGS}")
endif()

include_directories(.)

add_library(NodeJS SHARED
        NodeJS.hpp NodeJS.cpp)
target_link_libraries(NodeJS HttpParser_Core)

# install

install(
    TARGETS NodeJS
    LIBRARY DESTINATION lib/HttpParser/plugins
)
