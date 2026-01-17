#include "FileStream.hpp"
#include <iostream>

FileStream::FileStream(const std::string &path)
    : filepath(path), is_open(false)
{
    stream.open(path, std::ios::in | std::ios::out | std::ios::binary);

    if (stream.is_open())
    {
        is_open = true;
    }
    else
    {
        std::cerr << "Failed to open file: " << path << std::endl;
    }
}

FileStream::~FileStream()
{
    if (is_open && stream.is_open())
    {
        stream.close();
        is_open = false;
    }
}

std::fstream &FileStream::getStream()
{
    return stream;
}

bool FileStream::isOpen() const noexcept
{
    return is_open;
}

const std::string &FileStream::getFilePath() const noexcept
{
    return filepath;
}