#include <chrono>
#include <iostream>

#include "TaskScheduler.hpp"

using namespace std::chrono;

namespace {
inline std::string toString(
    const std::chrono::time_point<std::chrono::system_clock>& timePoint) {
  auto t{std::chrono::system_clock::to_time_t(timePoint)};
  return std::ctime(&t);
}
}  // namespace

int main() {
  TaskScheduler ts;
  using namespace std::chrono_literals;
  auto startTime{system_clock::now()};
  ts.scheduleAt(startTime + 1s, [startTime]() {
    std::cout << "call scheduled at: " << toString(startTime + 1s)
              << "(delay = "
              << duration_cast<microseconds>(system_clock::now() -
                                             (startTime + 1s))
                     .count()
              << "μs)" << std::endl;
  });
  ts.scheduleAfter(2s, [startTime]() {
    std::cout << "call scheduled 2sec after: " << toString(startTime)
              << "(delay = "
              << duration_cast<microseconds>(system_clock::now() -
                                             (startTime + 2s))
                     .count()
              << "μs)" << std::endl;
  });
  ts.scheduleEvery(3s, [startTime]() {
    static auto n{1};
    std::cout << "call scheduled every 3sec, after: " << toString(startTime)
              << "(delay = "
              << duration_cast<microseconds>(system_clock::now() -
                                             (startTime + 3s * n++))
                     .count()
              << "μs)" << std::endl;
  });
  ts.run();
  return 0;
}
