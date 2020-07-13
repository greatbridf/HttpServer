//
// Created by David Mike on 2020/7/13.
//

#include "Configurations.hpp"

namespace greatbridf
{
    void from_json(const json& json, Site& site)
    {
        json.at("handler").get_to(site.handler);
        json.at("path").get_to(site.path);
        json.at("rule").get_to(site.rule);
    }
    Configurations::Configurations(json&& __json)
        : _json(__json)
    {
        parseSites();
    }
    Configurations::Configurations(const std::string& _filename)
    {
        InputFile file(_filename);
        if (!file.readable())
        {
            throw Exception("permission denied: cannot read configuration file");
        }
        file >> _json;
        parseSites();
    }
    std::string Configurations::global_option(const std::string& key) const
    {
        std::string ret;
        try
        {
            ret = _json[key];
        }
        catch (nlohmann::json::type_error& err)
        {
            ret = "";
        }
        return ret;
    }
    bool Configurations::has_option(const std::string& key) const
    {
        return _json.contains(key);
    }
    const std::vector<Site>& Configurations::sites() const
    {
        return _sites;
    }
    void Configurations::parseSites()
    {
        if (!has_option("sites"))
        {
            return;
        }
        const auto& sites_elem = _json["sites"];
        _sites = sites_elem.get<std::vector<Site>>();
    }
}
