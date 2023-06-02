#include <iostream>
#include <thread>

#include "TaskScheduler.hpp"

using namespace std::chrono;

namespace {
inline auto toString(
    const std::chrono::time_point<std::chrono::system_clock>& timePoint) {
  auto t{std::chrono::system_clock::to_time_t(timePoint)};
  return std::ctime(&t);
}
}  // namespace

int main() {
  TaskScheduler ts;
  using namespace std::chrono_literals;
  auto startTime{system_clock::now()};
  auto t1 = ts.scheduleAt(startTime + 1s, [startTime]() {
    std::cout << "call scheduled at: " << toString(startTime + 1s)
              << "(delayed = "
              << duration_cast<microseconds>(system_clock::now() -
                                             (startTime + 1s))
                     .count()
              << "μs)" << std::endl;
  });
  auto t2 = ts.scheduleAfter(2s, [startTime]() {
    std::cout << "call scheduled after 2sec "
              << "(delayed = "
              << duration_cast<microseconds>(system_clock::now() -
                                             (startTime + 2s))
                     .count()
              << "μs)" << std::endl;
  });
  auto t3 = ts.scheduleEvery(3s, [startTime]() {
    static auto n{1};
    std::cout << "call scheduled every 3sec "
              << "(delayed = "
              << duration_cast<microseconds>(system_clock::now() -
                                             (startTime + 3s * n++))
                     .count()
              << "μs)" << std::endl;
  });

  auto taskCancelation{std::async([&ts, t1, t2, t3]() {
    std::this_thread::sleep_for(10s);
    std::cout << "canceling tasks..." << std::endl;
    ts.cancel(t1);
    ts.cancel(t2);
    ts.cancel(t3);
  })};

  ts.run();

  return 0;
}
