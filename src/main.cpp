#include "task.h"
#include <iostream>

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
        ++frame;
        auto stop = Clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

        if (duration.count() > time)
        {
            return true;
        }

        return false;
    }

    int GetFrame() { return frame; }

private:
    int time = 0;
    int frame = 0;
    Clock::time_point start;
};

Task Test(bool& b, int time)
{
    co_await BoolCondition(b, true);
    co_await Timer(time);
    co_await NextFrame();
}

int main()
{
    Application app(4000);
    bool b;
    Test(b, 1000);

    while (!app.ShouldClose())
    {
        b = true;
        Scheduler::GetInstance().Update();
    }
}