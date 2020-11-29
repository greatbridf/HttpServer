cmake_minimum_required(VERSION 3.15)
project(CoreHandlers)

set(CMAKE_CXX_STANDARD 17)
if (CMAKE_BUILD_TYPE STREQUAL Debug)
    set(CMAKE_CXX_FLAGS "-g -fPIC ${CMAKE_CXX_FLAGS}")
elseif (CMAKE_BUILD_TYPE STREQUAL Release)
    set(CMAKE_CXX_FLAGS "-O3 -fPIC ${CMAKE_CXX_FLAGS}")
elseif (CMAKE_BUILD_TYPE STREQUAL RelWithDebInfo)
    set(CMAKE_CXX_FLAGS "-g -O3 -fPIC ${CMAKE_CXX_FLAGS}")
endif()

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

# install

install(
        TARGETS GetHandler PostHandler PlainTextHandler
        LIBRARY DESTINATION lib/HttpParser/plugins
)
