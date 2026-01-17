#ifndef FILESTREAM_HPP
#define FILESTREAM_HPP

#include <fstream>
#include <string>
#include <memory>

class FileStream
{
private:
    std::fstream stream;
    std::string filepath;
    bool is_open;

public:
    explicit FileStream(const std::string &path);
    ~FileStream();

    // Prevent copying, allow moving for better performance
    FileStream(const FileStream &) = delete;
    FileStream &operator=(const FileStream &) = delete;
    FileStream(FileStream &&) noexcept = default;
    FileStream &operator=(FileStream &&) noexcept = default;

    std::fstream &getStream();
    bool isOpen() const noexcept;
    const std::string &getFilePath() const noexcept;
};

#endif