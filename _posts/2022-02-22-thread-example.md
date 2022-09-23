---
title: "std::thread example"
excerpt: "an example on a plane fueltank, it needs to land soon"
tags:
  - cpp
categories:
  - cpp
---

```cpp
#include <iostream>
#include <thread>
#include <chrono>
// g++ -lpthread

class FuelTank
{
private:
    std::thread CheckerTick;
    int fuel{8};
    bool runCheckerTask{true};

    void fuelCheckerTask(void)
    {
        while(runCheckerTask)
        {
            std::cout << "fuel checker, left: " << fuel << std::endl;
            if(fuel < 5 )
                std::cout << "land my friend" << std::endl;

            std::this_thread::sleep_for(std::chrono::milliseconds(80));
        }
    };

public:
    FuelTank()
    {
        std::cout << "create PeriodicChecker " << std::endl;
        // Thread with Member Function
        CheckerTick = std::thread(&FuelTank::fuelCheckerTask, this);
    };

    ~FuelTank()
    {
        runCheckerTask = false;
        // stop checker before deestroing this
        CheckerTick.join();
    };

    void useFuel(void)
    {
        if(fuel > 0) fuel--;
    };
};

int main()
{
    FuelTank check{};

    for(int i{20}; i>0; i--)
    {
        check.useFuel();
        std::cout << "use fuel.." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
};

// output:
// create PeriodicChecker 
// use fuel..
// fuel checker, left: 7
// fuel checker, left: 7
// use fuel..
// fuel checker, left: 6
// use fuel..
// fuel checker, left: 5
// use fuel..
// fuel checker, left: 4
// land my friend
// use fuel..
// [...]
```
