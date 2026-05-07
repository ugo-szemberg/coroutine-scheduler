#include "task.h"
#include <iostream>

bool can = false;

Task Test()
{
    std::cout << "bool false\n";
    co_await BoolCondition(can, true);
    std::cout << "bool true\n";
    std::cout << "timer started\n";
    co_await Timer(1000);
    std::cout << "timer finished\n";
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
    Application application(1000);

    Test();

    while (!application.ShouldClose())
    {
        Scheduler::GetInstance().Update();
    }
    can = true;
    Application application2(2000);

    while (!application2.ShouldClose())
    {
        Scheduler::GetInstance().Update();
    }
    can = false;
}