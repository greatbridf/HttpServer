//
// Created by David Mike on 2020/7/15.
//

#ifndef _CONSTANTS_HPP_
#define _CONSTANTS_HPP_

#ifndef _GREATBRIDF_BUFFER_SIZE
#define _GREATBRIDF_BUFFER_SIZE 8 * 1024 // 8k
#endif

#ifndef _GREATBRIDF_SOCKET_DEFAULT_TIMEOUT
#define _GREATBRIDF_SOCKET_DEFAULT_TIMEOUT 5 // 5 seconds
#endif

#ifndef _GREATBRIDF_SOCKET_QUEUE_MAX_LENGTH
#define _GREATBRIDF_SOCKET_QUEUE_MAX_LENGTH 16
#endif

#ifdef __APPLE__
#define _GREATBRIDF_PLUGIN_EXTENSION ".dylib"
#elif __unix__
#define _GREATBRIDF_PLUGIN_EXTENSION ".so"
#endif

// Daemon outputs
#define _GREATBRIDF_DAEMON_BADARGS "unexpected options"
#define _GREATBRIDF_DAEMON_PERMISSION_DENIED "permission denied"
#define _GREATBRIDF_DAEMON_NOT_RUNNING "program is not running"
#define _GREATBRIDF_DAEMON_ALREADY_RUNNING "program is already running"

#endif //_CONSTANTS_HPP_
