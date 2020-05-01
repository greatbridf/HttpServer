//
// Created by David Mike on 2020/5/1.
//

#include "PluginManager.hpp"

#include <filesystem>
#include <dlfcn.h>

namespace greatbridf
{
    PluginManager::~PluginManager()
    {
        for (auto& item : this->plugins)
        {
            delete item;
        }
    }
    void PluginManager::loadPlugins()
    {
        auto iter = std::filesystem::directory_iterator("./");
        std::filesystem::directory_iterator end;
        std::error_code err;
        for (; iter != end and !err; iter.increment(err))
        {
            auto ext = iter->path().extension().string();
            if (ext == ".dylib")
            {
                auto name = iter->path().filename().stem().string();
                auto handle = dlopen((name + ext).c_str(), RTLD_NOW);
                name = name.substr(3);
                auto func = (IPlugin* (*)())dlsym(handle, "registerPlugin");
                this->plugins.push_back(func());
                dlclose(handle);
            }
        }
    }
}
