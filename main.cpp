#include <iostream>
#include <filesystem>
#include <string>
#include <algorithm>
#include "./src/scheduler/job_scheduler.hpp"
#include "./src/scheduler/job.hpp"
#include "./src/file_stream/FileStream.hpp"

namespace fs = std::filesystem;

std::string getUserInput(const std::string& prompt) 
{
    std::string input;
    std::cout << prompt;
    std::getline(std::cin, input);
    return input;
}

std::string normalizeAction(const std::string& action) 
{
    std::string normalized = action;
    std::transform(normalized.begin(), normalized.end(), normalized.begin(), ::tolower);
    return normalized;
}

int main(int argc, char* argv[]) 
{
    std::string directoryPath = getUserInput("Enter the directory path: ");
    std::string actionInput = getUserInput("Enter the operation (encrypt/decrypt): ");
    
    std::string action = normalizeAction(actionInput);
    
    if (action != "encrypt" && action != "decrypt") 
    {
        std::cerr << "Error: Invalid operation. Use 'encrypt' or 'decrypt'" << std::endl;
        return 1;
    }
    
    try 
    {
        if (!fs::exists(directoryPath)) 
        {
            std::cerr << "Error: Directory does not exist: " << directoryPath << std::endl;
            return 1;
        }
        
        if (!fs::is_directory(directoryPath)) 
        {
            std::cerr << "Error: Path is not a directory: " << directoryPath << std::endl;
            return 1;
        }
        
        JobScheduler scheduler;
        size_t filesProcessed = 0;
        size_t filesSkipped = 0;
        
        for (const auto& entry : fs::recursive_directory_iterator(directoryPath)) 
        {
            if (!entry.is_regular_file()) 
            {
                continue;
            }
            
            std::string filepath = entry.path().string();
            FileStream fileHandler(filepath);
            std::fstream stream = std::move(fileHandler.getStream());
            
            if (!stream.is_open()) 
            {
                std::cerr << "Warning: Unable to open file: " << filepath << std::endl;
                filesSkipped++;
                continue;
            }
            
            Operation op = (action == "encrypt") ? Operation::ENCRYPT : Operation::DECRYPT;
            auto job = std::make_unique<Job>(std::move(stream), op, filepath);
            
            if (scheduler.enqueue(std::move(job))) 
            {
                filesProcessed++;
            }
        }
        
        std::cout << "\nFiles queued: " << filesProcessed << std::endl;
        if (filesSkipped > 0) 
        {
            std::cout << "Files skipped: " << filesSkipped << std::endl;
        }
        
        std::cout << "\nStarting " << action << " operations...\n" << std::endl;
        scheduler.processJobs();
        
        std::cout << "\nOperation completed successfully!" << std::endl;
        
    } 
    catch (const fs::filesystem_error& ex) 
    {
        std::cerr << "Filesystem error: " << ex.what() << std::endl;
        return 1;
    } 
    catch (const std::exception& ex) 
    {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1;
    }
    
    return 0;
}
