#include "task.h"

Scheduler::~Scheduler()
{
    for (auto& pair : tasks)
    {
        if (pair.second)
        {
            pair.second.destroy();
        }
    }
    tasks.clear();
}

Scheduler& Scheduler::GetInstance()
{
    static Scheduler scheduler;
    return scheduler;
}

void Scheduler::AddTask(Clock::time_point time, std::coroutine_handle<> task)
{
    tasks.push_back({ time, task });
}

void Scheduler::Update()
{
    auto now = Clock::now();
    for (auto it = tasks.begin(); it != tasks.end();)
    {
        if (now >= it->first)
        {
            it->second.resume();
            it = tasks.erase(it);
            continue;
        }
        ++it;
    }
}