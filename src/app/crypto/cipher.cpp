#include "cipher.hpp"
#include "../scheduler/tasks.hpp"
#include "../file_stream/env_reader.cpp"
#include <stdexcept>

int applyCipher(const std::string& jobData) 
{
    Job job = Job::deserialize(jobData);
    
    EnvReader envConfig;
    std::string keyStr = envConfig.loadEnv();
    
    if (keyStr.empty()) 
    {
        throw std::runtime_error("Failed to load encryption key from environment");
    }
    
    int shiftKey = std::stoi(keyStr);
    
    char byte;
    
    if (job.op == Operation::ENCRYPT) 
    {
        while (job.stream.get(byte)) 
        {
            byte = (byte + shiftKey) % 256;
            job.stream.seekp(-1, std::ios::cur);
            job.stream.put(byte);
        }
    } 
    else 
    {
        while (job.stream.get(byte)) 
        {
            byte = (byte - shiftKey + 256) % 256;
            job.stream.seekp(-1, std::ios::cur);
            job.stream.put(byte);
        }
    }
    
    if (job.stream.is_open()) 
    {
        job.stream.close();
    }
    
    return 0;
}