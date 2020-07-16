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

        const std::string& get(const std::string& key) const;

        bool has(const std::string& key) const;

        void clear();

        const std::map<std::string, std::string>& raw() const;

        friend std::istream& operator>>(std::istream& is, HTTPHeaders& headers);

     private:
        std::map<std::string, std::string> _headers;
    };

    template<>
    void HTTPHeaders::set<std::string>(const std::string& key, std::string value);

    template<>
    void HTTPHeaders::set<const char*>(const std::string& key, const char* value);
}

#endif //_HTTPHEADERS_HPP_
