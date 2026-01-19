#include "task_scheduler.hpp"
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <sys/wait.h>
// #include "../encryptDecrypt/Cryption.hpp"

JobScheduler::JobScheduler() {}

bool JobScheduler::enqueue(std::unique_ptr<Job> job) 
{
    if (!job)
    {
        return false;
    }
    
    jobQueue.push(std::move(job));
    return true;
}

void JobScheduler::processJobs() 
{
    while (!jobQueue.empty()) 
    {
        std::unique_ptr<Job> currentJob = std::move(jobQueue.front());
        jobQueue.pop();
        
        std::cout << "Processing job: " << currentJob->serialize() << std::endl;
        executeCryption(currentJob->serialize());
    }
}

size_t JobScheduler::queueSize() const noexcept
{
    return jobQueue.size();
}

bool JobScheduler::isEmpty() const noexcept
{
    return jobQueue.empty();
}