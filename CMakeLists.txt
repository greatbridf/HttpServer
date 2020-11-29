cmake_minimum_required(VERSION 3.15)
project(HttpParser)

set(CMAKE_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/prefix)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/HttpParser/plugins)

set(CMAKE_CXX_STANDARD 17)
if (CMAKE_BUILD_TYPE STREQUAL Debug)
    set(CMAKE_CXX_FLAGS "-g -fPIC ${CMAKE_CXX_FLAGS}")
    set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR})
elseif (CMAKE_BUILD_TYPE STREQUAL Release)
    set(CMAKE_CXX_FLAGS "-O3 -fPIC ${CMAKE_CXX_FLAGS}")
elseif (CMAKE_BUILD_TYPE STREQUAL RelWithDebInfo)
    set(CMAKE_CXX_FLAGS "-g -O3 -fPIC ${CMAKE_CXX_FLAGS}")
endif()

add_definitions(-D__PREFIX=\"${CMAKE_INSTALL_PREFIX}\")

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
add_dependencies(HttpParser GetHandler PostHandler PlainTextHandler NodeJS)

# plugins

#file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/plugins/)
file(COPY ${CMAKE_SOURCE_DIR}/Static/ConfigTemplate.json DESTINATION ${CMAKE_BINARY_DIR}/etc/HttpParser)
file(RENAME ${CMAKE_BINARY_DIR}/etc/HttpParser/ConfigTemplate.json ${CMAKE_BINARY_DIR}/etc/HttpParser/config.json)

add_subdirectory(HttpParser_Core)
add_subdirectory(Handler/Base)
add_subdirectory(Handler/Servlet)
add_subdirectory(Test)

# install

install(
        TARGETS HttpParser
        RUNTIME DESTINATION bin
)

install(
        FILES Static/ConfigTemplate.json
        DESTINATION etc/HttpParser
        RENAME config.json
)
