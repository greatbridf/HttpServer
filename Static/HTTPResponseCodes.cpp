//
// Created by David Mike on 2020/2/29.
//

#include "HTTPResponseCodes.hpp"

void init(std::map<int, std::string>& obj)
{
    // obj.insert(std::make_pair());
    obj.insert(std::make_pair(200, "OK"));
    obj.insert(std::make_pair(206, "Partial Content"));
    obj.insert(std::make_pair(400, "Bad Request"));
    obj.insert(std::make_pair(404, "Not Found"));
    obj.insert(std::make_pair(500, "Internal Server Error"));
}

const std::map<int, std::string>& greatbridf::Static::httpResponseCodes()
{
    static bool initialized = false;
    static std::map<int, std::string> obj;
    if (!initialized)
    {
        ::init(obj);
        initialized = true;
    }
    return obj;
}
