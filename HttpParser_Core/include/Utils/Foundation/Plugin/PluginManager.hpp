//
// Created by David Mike on 2020/5/1.
//

#ifndef _PLUGINMANAGER_HPP_
#define _PLUGINMANAGER_HPP_

#include "IPlugin.hpp"

#include <vector>

namespace greatbridf
{
    class PluginManager
    {
     public:
        ~PluginManager();
        void loadPlugins(const std::string& dir);
        const std::vector<IPlugin*>& getPlugins() const;
     private:
        std::vector<IPlugin*> plugins;
        std::vector<void*> handles;
    };
}

#endif //_PLUGINMANAGER_HPP_
