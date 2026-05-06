#include "task.h"
#include <iostream>

Task run()
{
    std::cout << "Starting timer...\n";
    co_await Timer(1000);
    std::cout << "Timer finished.\n";
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
    run();

    Application application(2000);

    while (!application.ShouldClose())
    {
        Scheduler::GetInstance().Update();
    }
}