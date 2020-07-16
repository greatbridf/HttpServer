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

#endif //_CONSTANTS_HPP_
