#include "FileStream.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <optional>

class EnvReader
{
private:
    static constexpr const char* ENV_FILE_PATH = ".env";

public:
    std::string loadEnv()
    {
        FileStream fs(ENV_FILE_PATH);
        
        if (!fs.isOpen())
        {
            std::cerr << "Warning: Could not load environment file" << std::endl;
            return "";
        }
        
        std::stringstream buffer;
        buffer << fs.getStream().rdbuf();
        return buffer.str();
    }
    
    std::optional<std::string> tryLoadEnv()
    {
        FileStream fs(ENV_FILE_PATH);
        
        if (!fs.isOpen())
        {
            return std::nullopt;
        }
        
        std::stringstream buffer;
        buffer << fs.getStream().rdbuf();
        std::string content = buffer.str();
        
        if (content.empty())
        {
            return std::nullopt;
        }
        
        return content;
    }
};