# Task Scheduler
A Simple Task Scheduler.
## Requirements
- C++ 17
- CMake 3.22.0
## Example
```cpp
#include <TaskScheduler.hpp>
#include <iostream>
#include <thread>

// ...

using namespace std::chrono;
using namespace std::chrono_literals;

TaskScheduler ts;

auto task1Id = ts.scheduleAt(system_clock::now() + 24h, [startTime]() {
  std::cout << "tomorrow" << std::endl;
});
auto task2Id = ts.scheduleAfter(2s, [startTime]() {
  std::cout << "after 2sec" << std::endl;
});
auto task3Id = ts.scheduleEvery(3s, [startTime]() {
  std::cout << "every 3sec " << std::endl;
});

auto std::thread t{ts.run()};

// ...

ts.cancel(task1Id);
ts.cancel(task2Id);
ts.cancel(task3Id),

// ...
```
