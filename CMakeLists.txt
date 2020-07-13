cmake_minimum_required(VERSION 3.15)
project(HttpParser)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-O3 -fPIC ${CMAKE_CXX_FLAGS}")

set(CMAKE_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/prefix)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/HttpParser/plugins)

if (CMAKE_BUILD_TYPE STREQUAL Debug)
    add_definitions(-D__PREFIX=\"${CMAKE_BINARY_DIR}\")
endif ()

include_directories(.)
include_directories(HttpParser_Core/include)
include_directories(src)
include_directories(third-party)

SET(HEADER
        src/marco_definitions.hpp)

SET(SOURCE
        src/RequestHandler.cpp)

add_executable(HttpParser Application.cpp main.cpp ${HEADER} ${SOURCE})
target_link_libraries(HttpParser HttpParser_Core pthread dl)

# plugins

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/plugins/)

add_subdirectory(HttpParser_Core)
add_subdirectory(Handler/Base)
add_subdirectory(Test)
