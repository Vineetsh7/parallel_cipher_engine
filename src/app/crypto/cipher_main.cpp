#include <iostream>
#include "cipher.hpp"

int main(int argc, char* argv[]) 
{
    if (argc != 2) 
    {
        std::cerr << "Usage: " << argv[0] << " <job_data>" << std::endl;
        return 1;
    }
    
    try 
    {
        applyCipher(argv[1]);
        std::cout << "Cipher operation completed successfully" << std::endl;
    } 
    catch (const std::exception& e) 
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
