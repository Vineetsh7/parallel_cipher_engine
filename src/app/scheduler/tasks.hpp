#ifndef TASKS_HPP
#define TASKS_HPP

#include "../file_stream/FileStream.hpp"
#include <fstream>
#include <string>
#include <sstream>
#include <stdexcept>

enum class Operation
{
    ENCRYPT,
    DECRYPT
};

struct Job
{
    std::string filepath;
    std::fstream stream;
    Operation op;

    Job(std::fstream &&fs, Operation operation, std::string path) 
        : stream(std::move(fs)), op(operation), filepath(std::move(path)) {}

    std::string serialize() const
    {
        std::ostringstream oss;
        oss << filepath << "," << (op == Operation::ENCRYPT ? "ENCRYPT" : "DECRYPT");
        return oss.str();
    }

    static Job deserialize(const std::string &data)
    {
        std::istringstream iss(data);
        std::string path;
        std::string opStr;

        if (!std::getline(iss, path, ',') || !std::getline(iss, opStr))
        {
            throw std::runtime_error("Invalid job data format");
        }

        Operation operation = (opStr == "ENCRYPT") ? Operation::ENCRYPT : Operation::DECRYPT;
        FileStream fileHandler(path);
        std::fstream fs = std::move(fileHandler.getStream());
        
        if (!fs.is_open())
        {
            throw std::runtime_error("Failed to open file: " + path);
        }

        return Job(std::move(fs), operation, std::move(path));
    }
};

#endif