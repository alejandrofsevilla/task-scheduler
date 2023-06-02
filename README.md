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

auto taskId1 = ts.scheduleAt(system_clock::now() + 24h, [startTime]() {
  std::cout << "tomorrow" << std::endl;
});
auto taskId2 = ts.scheduleAfter(2s, [startTime]() {
  std::cout << "after 2sec" << std::endl;
});
auto taskId3 = ts.scheduleEvery(3s, [startTime]() {
  std::cout << "every 3sec " << std::endl;
});

auto std::thread t{ts.run()};

// ...

ts.cancel(taskId1);
ts.cancel(taskId2);
ts.cancel(taskId3),

// ...
```
