//
// Created by David Mike on 2020/3/1.
//

#ifndef _ARGUMENTPARSER_HPP_
#define _ARGUMENTPARSER_HPP_

#include <string>
#include <vector>

namespace greatbridf
{
    class ArgumentParser
    {
     public:
        ArgumentParser(int argn, const char** argv);
        bool hasOption(const std::string& option) const;
        std::string getOption(const std::string& option) const;
     private:
        std::vector<std::string> args;
    };
}

#endif //_ARGUMENTPARSER_HPP_
