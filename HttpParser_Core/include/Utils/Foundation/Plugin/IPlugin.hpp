//
// Created by David Mike on 2020/5/1.
//

#ifndef _IPLUGIN_HPP_
#define _IPLUGIN_HPP_

#define __GREATBRIDF_DEFINE_PLUGIN_(plugin_name) \
namespace greatbridf {\
    class plugin_name : public IPlugin\
    {\
    public:\
        plugin_name();\
        ~plugin_name();\
    };\
}\
\
extern "C" greatbridf::IPlugin* registerPlugin()\
{\
    return new greatbridf::plugin_name();\
}

#include "../Types.hpp"
#include "IHTTPHandler.hpp"

namespace greatbridf
{
    class IPlugin : public virtual Interface
    {
     public:
        enum class PluginType
        {
            None,
            Handler,
        };

        explicit IPlugin(const char* _name, PluginType _type);
        ~IPlugin() override = default;

        const char* getName() const;
        PluginType getType() const;
        IHTTPHandler* handlerType() const;
        const void* getRawData() const;
     protected:
        const char* name = nullptr;
        void* impl = nullptr;
        PluginType type = PluginType::None;
    };
}

#endif //_IPLUGIN_HPP_
