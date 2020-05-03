#include "HTTPRequest.hpp"
#include <utils/Foundation/StringStream.hpp>

namespace greatbridf
{

    HTTPRequest::HTTPRequest()
        : type(HTTPRequestType::NONE), version(HTTPVersion::NONE)
    {
    }

    HTTPRequest::HTTPRequest(HTTPRequestType _type, std::string&& _path, HTTPVersion _version)
        : type(_type), version(_version)
    {
        this->path.str = _path;
    }

    const std::string& HTTPRequest::getQueryPath() const
    {
        return this->path.str;
    }

    HTTPRequestType HTTPRequest::getRequestType() const
    {
        return this->type;
    }

    HTTPVersion HTTPRequest::getHTTPVersion() const
    {
        return this->version;
    }

    std::istream& operator>>(std::istream& is, HTTPRequest& request)
    {
        request.clear();
        std::string tmp;

        // parse request type
        is >> tmp;
        if (!is.good()) return is;
        if (tmp == "GET") request.type = HTTPRequestType::GET;
        else if (tmp == "POST") request.type = HTTPRequestType::POST;
        else throw Exception("Unexpected query type");

        // parse request path
        is >> request.path;
        if (request.path.str == "/")
        {
            request.path.str = "/index.html";
        }

        // parse http version
        is >> tmp;
        if (tmp == "HTTP/1.1") request.version = HTTPVersion::ONE;
        else if (tmp == "HTTP/2") request.version = HTTPVersion::TWO;
        else throw Exception("unexpected http version");

        std::string key, value;

        // parse request head
        is.ignore(2);

        while (is.good() and is.peek() != '\r')
        {
            std::getline(is, key, ':');
            if (is.peek() == ' ') is.ignore();
            std::getline(is, value, '\r');
            is.ignore();

            std::transform(value.begin(), value.end(), value.begin(), ::tolower);
            request._headers.set(key, value);
        }
        is.ignore(2, '\n');

        return is;
    }

    size_t HTTPRequest::bodySize() const
    {
        auto str = _headers.get("Content-Length");
        if (str.empty())
        {
            return -1;
        }
        return std::stoi(str);
    }

    void HTTPRequest::clear()
    {
        type = HTTPRequestType::NONE;
        path.str.clear();
        version = HTTPVersion::NONE;
        _headers.clear();
    }
    std::vector<std::pair<size_t, size_t>> HTTPRequest::getRange() const
    {
        auto const& str = _headers.get("Range");
        std::vector<std::pair<size_t, size_t>> ret;
        if (str.empty())
        {
            return ret;
        }
        std::istringstream is(str);
        char c;
        size_t start, end = -1;
        while ((c = is.peek()) < '0' or c > '9') is.ignore();
        while (is.good())
        {
            is >> start;
            is.ignore();
            is >> end;
            ret.push_back(std::move(std::make_pair(start, end)));
            end = -1;
            while (is.good() and ((c = is.peek()) < '0' or c > '9')) is.ignore();
        }
        return ret;
    }
    std::string HTTPRequest::toString() const
    {
        OStringStream oss;
        oss << greatbridf::toString(this->type) << " "
            << this->path.str << " " << greatbridf::toString(this->version) << CRLF;
        for (const auto& item : this->_headers.raw())
        {
            oss << item.first << ": " << item.second << CRLF;
        }
        oss << CRLF;
        return oss.str();
    }
    HTTPHeaders& HTTPRequest::headers()
    {
        return this->_headers;
    }
}