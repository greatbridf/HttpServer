cmake_minimum_required(VERSION 3.15)
project(HttpParser)

set(CMAKE_CXX_STANDARD 20)
if (CMAKE_BUILD_TYPE STREQUAL Debug)
    set(CMAKE_CXX_FLAGS "-g -fPIC ${CMAKE_CXX_FLAGS}")
elseif (CMAKE_BUILD_TYPE STREQUAL Release)
    set(CMAKE_CXX_FLAGS "-O3 -fPIC ${CMAKE_CXX_FLAGS}")
elseif (CMAKE_BUILD_TYPE STREQUAL RelWithDebInfo)
    set(CMAKE_CXX_FLAGS "-g -O3 -fPIC ${CMAKE_CXX_FLAGS}")
endif()

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
        src/Application.h
        src/marco_definitions.hpp
        src/Configurations.hpp
        )

SET(SOURCE
        main.cpp
        src/Application.cpp
        src/RequestHandler.cpp
        src/Configurations.cpp
        )

add_executable(HttpParser ${HEADER} ${SOURCE})
target_link_libraries(HttpParser HttpParser_Core pthread dl)

# plugins

#file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/plugins/)

add_subdirectory(HttpParser_Core)
add_subdirectory(Handler/Base)
add_subdirectory(Test)
