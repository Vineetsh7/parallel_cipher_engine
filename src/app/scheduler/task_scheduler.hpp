#ifndef TASKS_SCHEDULER_HPP
#define TASKS_SCHEDULER_HPP

#include "tasks.hpp"
#include <queue>
#include <memory>

class JobScheduler
{
private:
    std::queue<std::unique_ptr<Job>> jobQueue;

public:
    JobScheduler();
    bool enqueue(std::unique_ptr<Job> job);
    void processJobs();
    size_t queueSize() const noexcept;
    bool isEmpty() const noexcept;
};

#endif