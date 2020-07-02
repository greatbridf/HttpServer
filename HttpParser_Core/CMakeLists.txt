cmake_minimum_required(VERSION 3.15)
project(HttpParser_Core)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-O3 -fPIC ${CMAKE_CXX_FLAGS}")

include_directories(include)

set(SOURCE
        src/Utils/Foundation/Exceptions/Exception.cpp
        src/Utils/Foundation/Exceptions/ExitException.cpp
        src/Utils/Foundation/LifeManagement/ArgumentParser.cpp
        src/Utils/Foundation/LifeManagement/Daemon.cpp
        src/Utils/Foundation/Plugin/IPlugin.cpp
        src/Utils/Foundation/Plugin/PluginManager.cpp
        src/Utils/Foundation/File.cpp
        src/Utils/Foundation/MIMETypes.cpp
        src/Utils/Foundation/StreamIOHelper.cpp
        src/Utils/Foundation/StringStream.cpp
        src/Utils/SocketIO/ServerSocket.cpp
        src/Utils/SocketIO/Socket.cpp
        src/Utils/SocketIO/SocketBuffer.cpp
        src/Utils/Thread/Thread.cpp
        src/HTTP/EnumToString.cpp
        src/HTTP/HTTPEscapedString.cpp
        src/HTTP/HTTPHeaders.cpp
        src/HTTP/HTTPRequest.cpp
        src/HTTP/HTTPResponse.cpp
        src/HTTP/HTTPResponseCodes.cpp
        src/HTTP/HTTPResponseHead.cpp
        )

add_library(HttpParser_Core ${SOURCE})
