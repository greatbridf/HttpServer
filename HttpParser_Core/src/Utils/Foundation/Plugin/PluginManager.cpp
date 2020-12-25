//
// Created by David Mike on 2020/5/1.
//

#include <Utils/Foundation/Plugin/PluginManager.hpp>

#include <filesystem>
#include <dlfcn.h>

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
    void PluginManager::loadPlugins(const std::string& dir)
    {
        std::filesystem::directory_iterator iter;
        iter = std::filesystem::directory_iterator(dir);
        std::filesystem::directory_iterator end;
        std::error_code err;
        for (; iter != end and !err; iter.increment(err))
        {
            auto path = iter->path();
            auto ext = path.extension().string();

            if (ext != _GREATBRIDF_PLUGIN_EXTENSION) continue;

            auto handle = dlopen(path.c_str(), RTLD_NOW);
            if (handle == nullptr)
            {
                auto err = dlerror();
                throw Exception("error found while registering plugin: invalid plugin handle : " + path.string() +
                            "\nerror info:\n" + err);
            }
            auto func = (PluginRegisterFunction)dlsym(handle, "registerPlugin");
            if (func == nullptr)
            {
                auto err = dlerror();
                throw Exception("error found while registering plugin: wrong format : " + path.string() +
                            "\nerror info:\n" + err);
            }

            this->plugins.push_back(func());
            this->handles.push_back(handle);
        }
    }
    const std::vector<IPlugin*>& PluginManager::getPlugins() const
    {
        return this->plugins;
    }
}
