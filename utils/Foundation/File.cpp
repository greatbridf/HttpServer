//
// Created by David Mike on 2020/2/26.
//

#include "File.hpp"

namespace greatbridf
{
    File::File(std::string _name)
        : _filename(std::move(_name)), std::fstream(_name)
    {
        seekg(0, std::ios::end);
        _fileSize = tellg();
        seekg(0, std::ios::beg);

    }
    size_t File::fileSize()
    {
        return _fileSize;
    }
    std::string File::getMimeType() const
    {
        auto const& mimeTypes = Static::mimeTypes();
        auto pos = _filename.rfind('.');
        if (pos == std::string::npos)
        {
            return mimeTypes.at("");
        }
        std::string ext = _filename.substr(pos + 1);
        if (mimeTypes.find(ext) == mimeTypes.end())
        {
            return mimeTypes.at("");
        }
        else
        {
            return mimeTypes.at(ext);
        }
    }
}
