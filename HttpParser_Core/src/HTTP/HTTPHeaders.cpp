//
// Created by David Mike on 2020/5/3.
//

#include <HTTP/HTTPHeaders.hpp>
#include <HTTP/HTTPRequest.hpp>

namespace greatbridf
{
    template<>
    void HTTPHeaders::set<std::string>(const std::string& key, std::string value)
    {
        this->_headers[key] = std::move(value);
    }
    template<>
    void HTTPHeaders::set<const char*>(const std::string& key, const char* value)
    {
        this->_headers[key] = value;
    }
    const std::string& HTTPHeaders::get(const std::string& key) const
    {
        return this->_headers.find(key) == this->_headers.end() ? NULL_STRING : this->_headers.at(key);
    }
    void HTTPHeaders::clear()
    {
        this->_headers.clear();
    }
    const std::map<std::string, std::string>& HTTPHeaders::raw() const
    {
        return this->_headers;
    }
    std::istream& operator>>(std::istream& is, HTTPHeaders& headers)
    {
        std::string key, value;
        while (is.good() and is.peek() != '\r')
        {
            std::getline(is, key, ':');
            if (is.peek() == ' ') is.ignore();
            std::getline(is, value, '\r');
            is.ignore();

            std::transform(value.begin(), value.end(), value.begin(), ::tolower);
            headers.set(key, value);
        }
        is.ignore(2, '\n');
        return is;
    }
}
