#include "task.h"
#include <iostream>

bool can = false;

Task TestTimer()
{
    std::cout << "starting timer\n";
    co_await Timer(1000);
    std::cout << "timer finished\n";
}

Task TestCondition()
{
    std::cout << "bool false\n";
    co_await BoolCondition(can, true);
    std::cout << "bool true\n";
}

class Application
{
public:
    Application(int _time)
    {
        time = _time;
        start = Clock::now();
    }
    ~Application() = default;

    bool ShouldClose()
    {
        auto stop = Clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

        if (duration.count() > time)
        {
            return true;
        }

        return false;
    }

private:
    int time = 0;
    Clock::time_point start;
};

int main()
{
    //TestTimer();
    TestCondition();

    Application application(1000);

    while (!application.ShouldClose())
    {
        Scheduler::GetInstance().Update();
    }
    can = true;
    Application application2(1000);

    while (!application2.ShouldClose())
    {
        Scheduler::GetInstance().Update();
    }
}