//
// Created by David Mike on 2020/7/13.
//

#ifndef _CONFIGURATIONS_HPP_
#define _CONFIGURATIONS_HPP_

#include <string>
#include <vector>

#include <HttpParser_Core.hpp>

#include <json.hpp>

using json = nlohmann::json;

namespace greatbridf
{
    class Configurations : public NonCopyable
    {
     public:
        explicit Configurations(const std::string& _filename);
        explicit Configurations(json&& __json);

        bool has_option(const std::string& key) const;
        std::string global_option(const std::string& key) const;

        const std::vector<Site>& sites() const;

     private:
        json _json;
        std::vector<Site> _sites;

        void parseSites();
    };
}

#endif //_CONFIGURATIONS_HPP_
