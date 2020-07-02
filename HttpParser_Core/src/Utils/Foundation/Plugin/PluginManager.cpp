//
// Created by David Mike on 2020/5/1.
//

#include <Utils/Foundation/Plugin/PluginManager.hpp>

#include <filesystem>
#include <dlfcn.h>

#ifdef __APPLE__
#define PLUGIN_EXTENSION ".dylib"
#else
#define PLUGIN_EXTENSION ".so"
#endif

namespace greatbridf
{
    PluginManager::~PluginManager()
    {
        auto len = this->plugins.size();
        for (int i = 0; i < len; ++i)
        {
            delete this->plugins[i];
            dlclose(this->handles[i]);
        }
    }
    void PluginManager::loadPlugins()
    {
        std::filesystem::directory_iterator iter;
        if (std::filesystem::exists("./plugins"))
        {
            iter = std::filesystem::directory_iterator("./plugins/");
        }
        else
        {
            iter = std::filesystem::directory_iterator("./");
        }
        std::filesystem::directory_iterator end;
        std::error_code err;
        for (; iter != end and !err; iter.increment(err))
        {
            auto ext = iter->path().extension().string();
            if (ext == PLUGIN_EXTENSION)
            {
                auto name = iter->path().filename().stem().string();
                auto handle = dlopen(std::string("./plugins/").append(name).append(ext).c_str(), RTLD_NOW);
                name = name.substr(3);
                auto func = (IPlugin* (*)())dlsym(handle, "registerPlugin");
                this->plugins.push_back(func());
                this->handles.push_back(handle);
            }
        }
    }
    const std::vector<IPlugin*>& PluginManager::getPlugins() const
    {
        return this->plugins;
    }
}
