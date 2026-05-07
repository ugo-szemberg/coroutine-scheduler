#include "task.h"

Scheduler::~Scheduler()
{
    for (auto& pair : timerTasks)
    {
        if (pair.second)
        {
            pair.second.destroy();
        }
    }
    timerTasks.clear();
}

void Scheduler::UpdateTimerTasks()
{
    auto now = Clock::now();
    for (auto it = timerTasks.begin(); it != timerTasks.end();)
    {
        if (now >= it->first)
        {
            it->second.resume();
            it = timerTasks.erase(it);
            continue;
        }
        ++it;
    }
}

void Scheduler::UpdateConditionTasks()
{
    for (auto it = boolConditionTasks.begin(); it != boolConditionTasks.end();)
    {
        if (*it->varToCheck == it->expectedValue)
        {
            it->task.resume();
            it = boolConditionTasks.erase(it);
            continue;
        }
        ++it;
    }
}

Scheduler& Scheduler::GetInstance()
{
    static Scheduler scheduler;
    return scheduler;
}

void Scheduler::AddTimerTask(Clock::time_point time, std::coroutine_handle<> task)
{
    timerTasks.push_back({ time, task });
}

void Scheduler::AddBoolConditionTask(bool* varToCheck, bool expectedValue, std::coroutine_handle<> task)
{
    BooleanCondition cb
    {
        .varToCheck = varToCheck,
        .expectedValue = expectedValue,
        .task = task
    };
    boolConditionTasks.push_back(cb);
}

void Scheduler::Update()
{
    UpdateTimerTasks();
    UpdateConditionTasks();
}