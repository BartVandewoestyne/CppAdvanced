#ifndef TEXT_FILE_READER_H
#define TEXT_FILE_READER_H

#include <fstream>
#include <string>

struct TextFileReader
{
    std::string m_path;

    TextFileReader(const std::string& path)
      : m_path(path)
    {}

    struct iterator {

        std::ifstream infile;

        std::string line;

        iterator()
        {}

        iterator(const std::string& path)
        {
            infile.open(path);
            std::getline(infile, line);
        }

        iterator& operator++()
        {
            if (!std::getline(infile, line))
            {
                 infile.close();
                 line.clear();
            };
            return *this;
        }

        bool operator==(const iterator& i)
        {
            return ( (infile.is_open() && i.infile.is_open())
                       && (line == i.line) ); 
        }

        bool operator!=(const iterator& i)
        {
            return !operator==(i);
        }

        std::string& operator*()
        {
            return line;
        }

    };

    iterator begin()
    {
        return iterator(m_path);
    }

    iterator end()
    {
        // How to get undefined behavior upon dereferencing this?
        return iterator();
    }

};

#endif  // TEXT_FILE_READER_H
