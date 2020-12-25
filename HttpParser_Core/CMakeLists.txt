cmake_minimum_required(VERSION 3.15)
project(HttpParser_Core)

set(CMAKE_CXX_STANDARD 17)
if (CMAKE_BUILD_TYPE STREQUAL Debug)
    set(CMAKE_CXX_FLAGS "-g -fPIC ${CMAKE_CXX_FLAGS}")
elseif (CMAKE_BUILD_TYPE STREQUAL Release)
    set(CMAKE_CXX_FLAGS "-O3 -fPIC ${CMAKE_CXX_FLAGS}")
elseif (CMAKE_BUILD_TYPE STREQUAL RelWithDebInfo)
    set(CMAKE_CXX_FLAGS "-g -O3 -fPIC ${CMAKE_CXX_FLAGS}")
endif()

include_directories(include)

set(HEADER
        include/HTTP/HTTPResponseHead.hpp
        include/HTTP/HTTPResponseCodes.hpp
        include/HTTP/HTTPResponse.hpp
        include/HTTP/HTTPRequest.hpp
        include/HTTP/HTTPHeaders.hpp
        include/HTTP/HTTPEscapedString.hpp
        include/HTTP/Base.hpp

        include/Utils/Foundation.hpp
        include/Utils/Foundation/Exceptions/Exception.hpp
        include/Utils/Foundation/Exceptions/ExitException.hpp
        include/Utils/Foundation/LifeManagement/ArgumentParser.hpp
        include/Utils/Foundation/LifeManagement/Daemon.hpp
        include/Utils/Foundation/Plugin/IHTTPHandler.hpp
        include/Utils/Foundation/Plugin/IPlugin.hpp
        include/Utils/Foundation/Plugin/PluginManager.hpp
        include/Utils/Foundation/BasicIO.hpp
        include/Utils/Foundation/Exceptions.hpp
        include/Utils/Foundation/File.hpp
        include/Utils/Foundation/LifeManagement.hpp
        include/Utils/Foundation/MIMETypes.hpp
        include/Utils/Foundation/Plugin.hpp
        include/Utils/Foundation/Serializable.hpp
        include/Utils/Foundation/StreamIOHelper.hpp
        include/Utils/Foundation/StringStream.hpp
        include/Utils/Foundation/Types.hpp

        include/Utils/SocketIO/ServerSocket.hpp
        include/Utils/SocketIO/Socket.hpp
        include/Utils/SocketIO/SocketBuffer.hpp

        include/Utils/Thread/Thread.hpp
        include/Utils/Thread/ITask.hpp

        include/HttpParser_Core.hpp
        include/constants.hpp
        include/Utils/Foundation/PosixCall.hpp
        )

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
        src/Utils/Foundation/pipe_exec.cpp
        )

add_library(HttpParser_Core ${SOURCE} ${HEADER})
