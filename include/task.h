#pragma once

#include <coroutine>
#include <chrono>
#include <vector>

using Clock = std::chrono::steady_clock;

class Scheduler
{
public:
    static Scheduler& GetInstance();

    void AddTask(Clock::time_point time, std::coroutine_handle<> task);
    void Update();

private:
    std::vector<std::pair<Clock::time_point, std::coroutine_handle<>>> tasks;

    Scheduler() = default;
    ~Scheduler();
};

struct Task
{
    struct promise_type
    {
        Task get_return_object() { return Task{ std::coroutine_handle<promise_type>::from_promise(*this) }; }
        std::suspend_never initial_suspend() noexcept { return {}; }
        std::suspend_never final_suspend() noexcept { return {}; }
        void return_void() {}
        void unhandled_exception() { std::terminate(); }
    };

    std::coroutine_handle<promise_type> handle{};
    explicit Task(std::coroutine_handle<promise_type> _handle) : handle(_handle) {}
    Task(Task&& pastTask) noexcept : handle(pastTask.handle)
    {
        pastTask.handle = {};
    }
    Task(const Task&) = delete;
    Task& operator=(const Task&) = delete;
};

struct Timer
{
    std::chrono::milliseconds duration;

    Timer(int milliseconds)
    {
        duration = std::chrono::milliseconds(milliseconds);
    }

    bool await_ready() const { return false; }
    void await_suspend(std::coroutine_handle<> h) const
    {
        Clock::time_point d = Clock::now() + duration;
        Scheduler::GetInstance().AddTask(d, h);
    }
    void await_resume() const {}
};