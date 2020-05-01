//
// Created by David Mike on 2020/5/1.
//

#include "IPlugin.hpp"

greatbridf::IPlugin::IPlugin(const char* _name, PluginType _type)
{
    this->name = _name;
    this->type = _type;
}
const char* greatbridf::IPlugin::getName() const
{
    return this->name;
}
greatbridf::IPlugin::PluginType greatbridf::IPlugin::getType() const
{
    return this->type;
}
