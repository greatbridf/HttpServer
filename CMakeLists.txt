cmake_minimum_required(VERSION 3.15)
project(HttpParser)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-O3 ${CMAKE_CXX_FLAGS}")

include_directories(.)
include_directories(HTTP)
include_directories(utils)
include_directories(utils/multi-threading)

add_library(HttpParser_Core STATIC
        HTTP/HTTPRequest.cpp
        HTTP/HTTPRequest.hpp
        utils/multi-threading/ITask.hpp
        utils/multi-threading/Thread.cpp
        utils/multi-threading/Thread.hpp
        utils/Foundation/Exceptions/Exception.cpp
        utils/Foundation/Exceptions/Exception.hpp
        utils/SocketIO/ServerSocket.cpp
        utils/SocketIO/ServerSocket.hpp
        utils/SocketIO/Socket.cpp
        utils/SocketIO/Socket.hpp
        Application.cpp
        Application.h
        HTTP/HTTPResponse.hpp
        HTTP/HTTPResponse.cpp
        utils/Foundation/Serializable.hpp
        HTTP/HTTPResponseHead.hpp
        HTTP/Base.hpp
        utils/SocketIO/SocketBuffer.cpp
        utils/SocketIO/SocketBuffer.hpp
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
        Static/HTTPResponseCodes.cpp
        utils/Foundation/LifeManagement/ArgumentParser.cpp
        utils/Foundation/LifeManagement/ArgumentParser.hpp
        utils/Foundation/Exceptions/ExitException.cpp
        utils/Foundation/Exceptions/ExitException.hpp
        utils/Foundation/File.cpp
        Static/CommandLineOutput.hpp
        utils/Foundation/LifeManagement/Daemon.cpp
        utils/Foundation/LifeManagement/Daemon.hpp
        Handler/IHTTPHandler.hpp
        utils/Foundation/Plugin/IPlugin.hpp
        utils/Foundation/Plugin/IPlugin.cpp
        utils/Foundation/Plugin/PluginManager.cpp
        utils/Foundation/Plugin/PluginManager.hpp)

add_executable(HttpParser main.cpp)
target_link_libraries(HttpParser HttpParser_Core)

add_subdirectory(Handler/Base)
