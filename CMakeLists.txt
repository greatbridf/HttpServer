cmake_minimum_required(VERSION 3.15)
project(HttpParser)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(HTTP)
include_directories(utils)
include_directories(utils/multi-threading)

add_executable(HttpParser
        HTTP/HTTPRequest.cpp
        HTTP/HTTPRequest.hpp
        utils/multi-threading/ITask.hpp
        utils/multi-threading/Thread.cpp
        utils/multi-threading/Thread.hpp
        utils/Exception.cpp
        utils/Exception.hpp
        utils/ServerSocket.cpp
        utils/ServerSocket.hpp
        utils/Socket.cpp
        utils/Socket.hpp
        Application.cpp
        Application.h
        main.cpp)