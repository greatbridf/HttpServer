//
// Created by David Mike on 2020/5/3.
//

#ifndef _HTTPHEADERS_HPP_
#define _HTTPHEADERS_HPP_

#include <map>
#include <string>

namespace greatbridf
{
    class HTTPHeaders
    {
     public:
        template<typename T>
        void set(const std::string& key, T value)
        {
            this->_headers[key] = std::to_string(value);
        }

        template<>
        void set<std::string>(const std::string& key, std::string value);

        template<>
        void set<const char*>(const std::string& key, const char* value);

        const std::string& get(const std::string& key) const;

        void clear();

        const std::map<std::string, std::string>& raw() const;

     private:
        std::map<std::string, std::string> _headers;
    };
}

#endif //_HTTPHEADERS_HPP_
