cmake_minimum_required(VERSION 3.15)
project(HttpParser)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-O3 ${CMAKE_CXX_FLAGS}")

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
        main.cpp
        HTTP/HTTPResponse.hpp
        HTTP/HTTPResponse.cpp
        utils/Foundation/Serializable.hpp
        HTTP/HTTPResponseHead.hpp
        HTTP/Base.hpp
        utils/SocketIO/SocketBuffer.cpp
        utils/SocketIO/SocketBuffer.hpp
        utils/Foundation/File.cpp
        utils/Foundation/File.hpp
        utils/Foundation/StreamIOHelper.hpp
        Handler/GETHandler.hpp
        Handler/GETHandler.cpp
        utils/Foundation/BasicIO.hpp
        utils/Foundation/StreamIOHelper.cpp
        Handler/POSTHandler.cpp
        Handler/POSTHandler.hpp
        HTTP/HTTPEscapedString.cpp
        HTTP/HTTPEscapedString.hpp
        HTTP/HTTPEscapedString.hpp
        Static/MIMETypes.hpp
        Static/MIMETypes.cpp
        Static/HTTPResponseCodes.hpp
        Static/HTTPResponseCodes.cpp)
