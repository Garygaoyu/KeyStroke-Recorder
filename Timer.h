#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <thread>

class Timer
{
    std::thread Thread;
    bool Active = false;
    long CallNumber = -1L;
    long Repeat_count = -1L;
    std::chrono::milliseconds interval = std::chrono::milliseconds(0);
    std::function<void(void)> func = nullptr;

    void SleepAndRun()
    {
        std::this_thread::sleep_for(interval);
        if(Active)
            Function()();
    }

    void ThreadFunc()
    {
        if(CallNumber == Infinite)
            while(Active)
              SleepAndRun();
        else
            while(Repeat_count--)
              SleepAndRun();
    }

public:
    static const long Infinite = -1L;

    Timer(){};

    Timer(const std::function<void(void)> &f) : func(f) {}

    Timer(const std::function<void(void)> &f,
          const unsigned long &i,
          const long Repeat = Timer::Infinite) : func(f),
                                                 interval(std::chrono::milliseconds(i)),
                                                 CallNumber(Repeat) {}


    void StartTimer(bool Async = true)
    {
        if(IsActive())
            return;
        Active = true;
        Repeat_count = CallNumber;
        if(Async)
            Thread = std::thread(ThreadFunc, this);
        else
            this->ThreadFunc();
    }

    void StopTimer()
    {
        Active = false;
        Thread.join();
    }

    void SetFunction(const std::function<void(void)> &f)
    {
        func = f;
    }

    bool IsActive() const {return Active;}

    void RepeatCount (const long r)
    {
        if(Active)
            return;
        CallNumber = r;
    }

    long RepeatCount() const {return CallNumber;}

    long GetLeftCount() const {return Repeat_count;}

    void SetInterval(const unsigned long &i)
    {
        if(Active)
            return;
        interval = std::chrono::milliseconds(i);
    }

    unsigned long Interval() const {return interval.count();}

    const std::function<void(void)> &Function() const
    {
        return func;
    }

};


#endif // TIMER_H
