//
// Created by David Mike on 2020/3/1.
//

#ifndef _COMMANDLINEOUTPUT_HPP_
#define _COMMANDLINEOUTPUT_HPP_

namespace greatbridf::Static::CommandLineOutput
{
    inline const char* badArgs = "HttpParser: Unexpected options";
    inline const char* permissionDenied = "HttpParser: permission denied";
    inline const char* notRunning = "HttpParser: program is not running";
    inline const char* alreadyRunning = "HttpParser: program is already running";
    inline const char* help = "Usage: HttpParser [-d start|stop]\n"
                              "\n"
                              "  -d start|stop    Run or stop on background";
}

#endif //_COMMANDLINEOUTPUT_HPP_
