//
// Created by David Mike on 2020/2/26.
//

#ifndef HTTPPARSER_FILE_HPP
#define HTTPPARSER_FILE_HPP

#include <string>
#include <fstream>
#include <Static/MIMETypes.hpp>

namespace greatbridf
{
    class File : public std::fstream
    {
     public:
        explicit File(std::string name);
        size_t fileSize();

        std::string getMimeType() const;

     private:
        std::string _filename;
        size_t _fileSize;

    };

}

#endif //HTTPPARSER_FILE_HPP
