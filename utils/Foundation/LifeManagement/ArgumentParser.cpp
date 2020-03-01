//
// Created by David Mike on 2020/3/1.
//

#include "ArgumentParser.hpp"

namespace greatbridf
{
    ArgumentParser::ArgumentParser(int argn, const char** argv)
    {
        for (int i = 0; i < argn; ++i)
        {
            args.push_back(std::move(std::string(argv[i])));
        }
    }
    bool ArgumentParser::hasOption(const std::string& option) const
    {
        for (auto& arg : args)
        {
            if (arg == option)
            {
                return true;
            }
        }
        return false;
    }
    std::string ArgumentParser::getOption(const std::string& option) const
    {
        auto size = args.size();
        for (int i = 0; i < size; ++i)
        {
            if (args[i] == option)
            {
                if (i + 1 == size) break;
                return args[i + 1];
            }
        }
        return std::string();
    }
}
